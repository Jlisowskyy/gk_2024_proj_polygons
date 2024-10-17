//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "../include/GraphicObjects/Point.h"
#include "../include/Constants.h"
#include "../include/ManagingObjects/Polygon.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/DrawingWidget.h"
#include "../include/Interfaces/IPointPolygonObject.h"
#include "../include/Restrictions/ObjectRestriction.h"

/* external includes */
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QVariant>

Point::Point(const int x, const int y, Polygon *polygon) : QGraphicsEllipseItem(0,
                                                                                0,
                                                                                DEFAULT_POINT_RADIUS * 2,
                                                                                DEFAULT_POINT_RADIUS * 2),
                                                           IConnectableElement<Edge>(reinterpret_cast<void *>(this)),
                                                           IPointPolygonObject(this, polygon),
                                                           m_pointId(polygon->getAndIncrementPointCount()) {
    setFlags(flags() | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsScenePositionChanges);
    setPen(QPen(DEFAULT_COLOR));
    setBrush(QBrush(DEFAULT_COLOR));
    setPos(QPointF(x - DEFAULT_POINT_RADIUS, y - DEFAULT_POINT_RADIUS));

    /* Points should be displayed above edges */
    setZValue(1);

    /* display point Id above the point */
    QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(m_pointId), this);
    text->setPos(-POINT_ID_DIST, -POINT_ID_DIST);
}

QVariant Point::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case GraphicsItemChange::ItemSelectedHasChanged:
            return _onSelectionChange(value);
        case GraphicsItemChange::ItemPositionHasChanged:
            return _onPositionChanged(value);
        case GraphicsItemChange::ItemSceneHasChanged:
            if (scene() == nullptr) {
                onRemoved();
            }
            return value;
        default:
            return QGraphicsEllipseItem::itemChange(change, value);
    }
}

QVariant Point::_onSelectionChange(const QVariant &value) {
    setPen(QPen(isSelected() ? SELECTED_COLOR : DEFAULT_COLOR));
    setBrush(QBrush(isSelected() ? SELECTED_COLOR : DEFAULT_COLOR));

    const QPointF center = rect().center();
    const auto radius = getRadius();
    setRect(QRectF(
            center.x() - radius,
            center.y() - radius,
            radius * 2,
            radius * 2
    ));

    return value;
}


QPointF Point::getPositionOnPainter() const {
    const auto radius = getRadius();
    const auto pos = scenePos() + QPointF(radius, radius);

    return pos;
}

QVariant Point::_onPositionChanged(const QVariant &value) {
    if (m_restriction) {
        m_restriction->onReposition();
    }

    qDebug() << "Point position changed: " << value.toPointF();

    _propagatePositionChange();
    m_prevPos = scenePos();
    return value;
}

double Point::getRadius() const {
    return static_cast<double>(isSelected() ? SELECTED_POINT_RADIUS : DEFAULT_POINT_RADIUS);
}

void Point::setPositionOnPainter(const QPointF &position) {
    setPos(position - QPointF(getRadius(), getRadius()));
}

Point *Point::getConnectedPoint(const size_t direction) const {
    Edge *edge = getConnectedElement(direction);
    if (edge == nullptr) {
        return nullptr;
    }

    Point *point = edge->getConnectedElement(direction);
    Q_ASSERT(point != nullptr);
    return point;
}

void Point::_propagatePositionChange() {
    if (BlockPropagation) {
        return;
    }

    QPointF dxdy = scenePos() - m_prevPos;

    BlockPropagation = true;

    if (!m_polygon->isFullPolygon()) {
        if (Point *point = getConnectedPoint(LEFT)) {
            const bool result = point->tryToPreserveRestrictions(dxdy, LEFT, nullptr, false);
            Q_ASSERT(result);
        }

        if (Point *point = getConnectedPoint(RIGHT)) {
            const bool result = point->tryToPreserveRestrictions(dxdy, RIGHT, nullptr, false);
            Q_ASSERT(result);
        }
    } else {
        _fullPolygonPositionChange(dxdy);
    }

    updateEdgePositions();
    BlockPropagation = false;
}

bool
Point::tryToPreserveRestrictions(const QPointF dxdy, const size_t direction, Point *blockPoint, const bool dryRun) {
    if (blockPoint == reinterpret_cast<void *>(this)) {
        return areRestrictionsPreserved();
    }

    if (areRestrictionsPreserved()) {
        return true;
    }

    const size_t reversedDirection = swapDirection(direction);
    Edge *edge = getConnectedElement(reversedDirection);
    Q_ASSERT(edge);

    const QPointF restrictionDxdy = edge->getRestriction()->tryToPreserveRestriction(direction, dxdy);
    moveBy(restrictionDxdy.x(), restrictionDxdy.y());
    const bool result = (!getConnectedPoint(direction) ||
                         getConnectedPoint(direction)->tryToPreserveRestrictions(dxdy, direction, blockPoint, dryRun));

    if (!result || dryRun) {
        moveBy(-restrictionDxdy.x(), -restrictionDxdy.y());
    }

    return result;
}

Point *Point::getDistantPoint(const size_t direction, const uint distance) const {
    Point *point = getConnectedPoint(direction);

    if (distance == 0) {
        return point;
    }

    if (point == nullptr) {
        return nullptr;
    }

    return point->getDistantPoint(direction, distance - 1);
}

int Point::countPoints() {
    int count = 0;

    iteratePoints([&count](Point *) {
        count++;
    });

    return count;
}

void Point::_fullPolygonPositionChange(const QPointF dxdy) {
    moveWholePolygon(dxdy);
    return;

    const int pointCount = countPoints();

    Point *leftBlock = nullptr;
    Point *rightBlock = nullptr;

    if (pointCount % 2 == 0) {
        const int midPointDist = (pointCount / 2) - 1;
        leftBlock = getDistantPoint(LEFT, midPointDist);
        rightBlock = leftBlock;
    } else {
        const int blockPointDist = (pointCount / 2);
        leftBlock = getDistantPoint(LEFT, blockPointDist);
        rightBlock = getDistantPoint(RIGHT, blockPointDist);
    }

    Q_ASSERT(leftBlock && rightBlock);

    const bool leftSuccess = getConnectedPoint(LEFT)->tryToPreserveRestrictions(dxdy, LEFT, leftBlock, true);

    if (!leftSuccess) {
        moveWholePolygon(dxdy);
        qDebug() << "Failed: moved whole polygon";
        return;
    }

    const bool rightSuccess = getConnectedPoint(RIGHT)->tryToPreserveRestrictions(dxdy, RIGHT, rightBlock, true);

    if (!rightSuccess) {
        moveWholePolygon(dxdy);
        qDebug() << "Failed: moved whole polygon";
        return;
    }

    const bool resultLeft = getConnectedPoint(LEFT)->tryToPreserveRestrictions(dxdy, LEFT, leftBlock, true);
    const bool resultRight = getConnectedPoint(RIGHT)->tryToPreserveRestrictions(dxdy, RIGHT, rightBlock, true);

    Q_ASSERT(resultLeft && resultRight);
}

void Point::moveWholePolygon(const QPointF dxdy) {
    iteratePoints([dxdy, this](Point *point) {
        if (point != this) {
            point->moveBy(dxdy.x(), dxdy.y());
        }
    });
}

bool Point::areRestrictionsPreserved() {
    return (!getConnectedElement(LEFT) || getConnectedElement(LEFT)->isRestrictionPreserved()) &&
           (!getConnectedElement(RIGHT) || getConnectedElement(RIGHT)->isRestrictionPreserved());
}

void Point::updateEdgePositions() {
    iterateEdges([](Edge *edge) {
        edge->repositionByPoints();
    });
}


