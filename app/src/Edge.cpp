//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "../include/GraphicObjects/Edge.h"
#include "../include/Constants.h"
#include "../include/GraphicObjects/DrawingWidget.h"
#include "../include/Restrictions/ObjectRestriction.h"

/* external includes */
#include <QPen>
#include <QDebug>
#include <QPainter>
#include <cmath>

#include "../include/Restrictions/EdgeBezierRestriction.h"
#include "../include/Restrictions/PointC1ContinuousRestriction.h"

Edge::Edge(Point *start, Point *end, DrawingWidget *drawingWidget, Polygon *polygon) : QGraphicsLineItem(
                                                                                           QLineF(start->getPositionOnPainter(),
                                                                                                  end->getPositionOnPainter())),
                                                                                       IConnectableElement<Point>(
                                                                                           reinterpret_cast<void *>(this)),
                                                                                       IEdgePolygonObject(this,
                                                                                                          polygon),
                                                                                       m_drawingWidget(drawingWidget) {
    Q_ASSERT(start != nullptr && end != nullptr);

    QPen pen(DEFAULT_COLOR);
    pen.setWidth(DEFAULT_EDGE_WIDTH);
    setPen(pen);

    /* Edges should be displayed under points */
    setZValue(0);

    setFlag(QGraphicsItem::ItemIsSelectable, true);
    //    setFlag(QGraphicsItem::ItemIsMovable, true);
    //    setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);

    setConnectedElement(LEFT, start);
    setConnectedElement(RIGHT, end);
}

QVariant Edge::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case GraphicsItemChange::ItemPositionChange:
            return _onPositionChange(value);
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
            return QGraphicsLineItem::itemChange(change, value);
    }
}

/**
 *
 * @note Preserves transparency!
 */
QVariant Edge::_onSelectionChange(const QVariant &value) {
    QPen currentPen = pen();
    QColor currentColor = currentPen.color();
    int alpha = currentColor.alpha();

    QColor newColor = isSelected() ? SELECTED_COLOR : DEFAULT_COLOR;
    newColor.setAlpha(alpha);

    QPen pen(newColor);
    pen.setWidth(isSelected() ? SELECTED_EDGE_WIDTH : DEFAULT_EDGE_WIDTH);
    setPen(pen);

    return value;
}

QVariant Edge::_onPositionChange(const QVariant &value) {
    return value;
}

QVariant Edge::_onPositionChanged(const QVariant &value) {
    if (m_restriction) {
        m_restriction->onReposition();
    }

    _propagatePositionChange(value.toPointF());
    return value;
}

bool Edge::repositionByPoints() {
    verifyRestrictions();

    if (line().p1() == getConnectedElement(LEFT)->getPositionOnPainter() &&
        line().p2() == getConnectedElement(RIGHT)->getPositionOnPainter()) {
        return false;
    }

    if (!m_isUpdating) {
        setLine(QLineF(getConnectedElement(LEFT)->getPositionOnPainter(),
                       getConnectedElement(RIGHT)->getPositionOnPainter()));
        setPos({0, 0});

        if (m_restriction) {
            m_restriction->onReposition();
        }
    }

    return true;
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    switch (m_drawingWidget->getLineDrawingAlgorithm()) {
        case DEFAULT:
            QGraphicsLineItem::paint(painter, option, widget);
            return;
        case BRESENHAM:
            _bresenhamLine(painter);
            return;
        default:
            Q_ASSERT(false);
    }
}

bool Edge::applyRestriction(ObjectRestriction *restriction, DrawingWidget *drawingWidget) {
    const bool result = IEdgePolygonObject::applyRestriction(restriction, drawingWidget);

    if (!result && dynamic_cast<EdgeBezierRestriction *>(restriction) != nullptr) {
        Point *pLeft = getConnectedElement(LEFT);
        Point *pRight = getConnectedElement(RIGHT);

        Q_ASSERT(pLeft && pRight);

        if (pLeft->getRestriction() == nullptr) {
            pLeft->applyRestriction(new PointC1ContinuousRestriction(pLeft), drawingWidget);
        }

        if (pRight->getRestriction() ==nullptr) {
            pRight->applyRestriction(new PointC1ContinuousRestriction(pRight), drawingWidget);
        }
    }

    return result;
}

void Edge::_bresenhamLine(QPainter *painter) {
    QPen pen = this->pen();
    painter->setPen(pen);

    QLineF line = this->line();
    QPointF p1 = line.p1();
    QPointF p2 = line.p2();

    int x1 = static_cast<int>(p1.x());
    int y1 = static_cast<int>(p1.y());
    int x2 = static_cast<int>(p2.x());
    int y2 = static_cast<int>(p2.y());

    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;

    while (true) {
        painter->drawPoint(x1, y1);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void Edge::cutEdge(DrawingWidget *drawingWidget) {
    Point *pLeft = getConnectedElement(LEFT);
    Point *pRight = getConnectedElement(RIGHT);

    QPoint midPos = getMidPoint().toPoint();

    Point *pMid = drawingWidget->addPoint(midPos.x(), midPos.y());
    Edge *leftEdge = drawingWidget->addEdge(pLeft, pMid);
    Edge *rightEdge = drawingWidget->addEdge(pMid, pRight);

    pLeft->setConnectedElement(RIGHT, leftEdge);
    pMid->setConnectedElement(LEFT, leftEdge);
    pMid->setConnectedElement(RIGHT, rightEdge);
    pRight->setConnectedElement(LEFT, rightEdge);

    setConnectedElement(LEFT, nullptr);
    setConnectedElement(RIGHT, nullptr);

    m_drawingWidget->scene()->removeItem(this);
}

QPointF Edge::getMidPoint() const {
    Point *pLeft = getConnectedElement(LEFT);
    Point *pRight = getConnectedElement(RIGHT);
    const auto pLeftPos = pLeft->getPositionOnPainter();
    const auto pRightPos = pRight->getPositionOnPainter();

    return (pLeftPos + pRightPos) / 2.0;
}

double Edge::getLength() const {
    Point *pLeft = getConnectedElement(LEFT);
    Point *pRight = getConnectedElement(RIGHT);
    const auto pLeftPos = pLeft->getPositionOnPainter();
    const auto pRightPos = pRight->getPositionOnPainter();

    const double xDiff = pRightPos.x() - pLeftPos.x();
    const double yDiff = pRightPos.y() - pLeftPos.y();

    return std::sqrt(xDiff * xDiff + yDiff * yDiff);
}

void Edge::_propagatePositionChange(QPointF point) {
    if (BlockPropagation) {
        return;
    }

    m_isUpdating = true;
    getConnectedElement(LEFT)->setPositionOnPainter(line().p1() + point);
    getConnectedElement(RIGHT)->setPositionOnPainter(line().p2() + point);
    m_isUpdating = false;
}

void Edge::verifyRestrictions() const {
    if (!m_restriction) {
        return;
    }

    const bool result = m_restriction->isRestrictionPreserved();

    if (!result) {
        qDebug() << "[ WARNING: EDGE ]: Edge restriction is not preserved!";
    }
}
