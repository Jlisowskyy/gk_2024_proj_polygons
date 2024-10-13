//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Point.h"
#include "Constants.h"
#include "Polygon.h"
#include "Edge.h"
#include "Painter.h"

/* external includes */
#include <QPen>
#include <QBrush>
#include <QDebug>

Point::Point(const int x, const int y) : QGraphicsEllipseItem(0,
                                                              0,
                                                              DEFAULT_POINT_RADIUS * 2,
                                                              DEFAULT_POINT_RADIUS * 2),
                                         IConnectableElement<Edge>() {
    setFlags(flags() | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsScenePositionChanges);
    setPen(QPen(DEFAULT_COLOR));
    setBrush(QBrush(DEFAULT_COLOR));
    setPos(QPointF(x - DEFAULT_POINT_RADIUS, y - DEFAULT_POINT_RADIUS));

    /* Points should be displayed above edges */
    setZValue(1);
}

QVariant Point::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case GraphicsItemChange::ItemPositionChange:
            return _onPositionChange(value);
        case GraphicsItemChange::ItemSelectedHasChanged:
            return _onSelectionChange(value);
        case GraphicsItemChange::ItemPositionHasChanged:
            return _onPositionChanged(value);
        default:
            return QGraphicsEllipseItem::itemChange(change, value);
    }
}

QVariant Point::_onPositionChange(const QVariant &value) {
    return value;
}

QVariant Point::_onSelectionChange(const QVariant &value) {
    setPen(QPen(isSelected() ? SELECTED_COLOR : DEFAULT_COLOR));
    setBrush(QBrush(isSelected() ? SELECTED_COLOR : DEFAULT_COLOR));

    const auto prevRadius = rect().width() / 2;
    const auto radius = getRadius();
    setRect(QRectF(
            0,
            0,
            radius * 2,
            radius * 2
    ));

    const double offset = prevRadius - radius;
    setPos(scenePos() + QPointF(offset, offset));

    return value;
}

QPointF Point::getPositionOnPainter() const {
    const auto radius = getRadius();
    const auto pos = scenePos() + QPointF(radius, radius);

    return pos;
}

QVariant Point::_onPositionChanged(const QVariant &value) {
    for (auto &m_edge: m_connectedElements) {
        if (m_edge) {
            m_edge->repositionByPoints();
        }
    }

    return value;
}

double Point::getRadius() const {
    return static_cast<double>(isSelected() ? SELECTED_POINT_RADIUS : DEFAULT_POINT_RADIUS);
}

std::tuple<Point *, Point *> Point::remove(const bool isFullPolygon, Painter *const painter) {
    Point *connections[MAX_CONNECTIONS]{};
    Point *start{};
    Point *end{};

    /* Gather connections */
    for (size_t direction = 0; direction < MAX_CONNECTIONS; ++direction) {
        if (Edge *itemToRemove = getConnectedElement(direction); itemToRemove != nullptr) {
            connections[direction] = itemToRemove->getConnectedElement(direction);
            Q_ASSERT(connections[direction] != nullptr);

            connections[direction]->setConnectedElement(SwapDirection(direction), nullptr);

            scene()->removeItem(itemToRemove);
        }
    }

    /* Add edge except triangle case */
    if (connections[0] != nullptr &&
        connections[1] != nullptr &&
        !(isFullPolygon &&
          static_cast<void *>(connections[1]->getConnectedElement(RIGHT)) != static_cast<void *>(connections[0]))) {

        Edge *edge = painter->addEdge(connections[0], connections[1]);
        connections[0]->setConnectedElement(RIGHT, edge);
        connections[1]->setConnectedElement(LEFT, edge);
    }

    /* Prepare new start and end */
    if (isFullPolygon) {
        Q_ASSERT(connections[0] != nullptr && connections[1] != nullptr);

        start = connections[1];
        end = connections[0];
    } else {
        if (connections[0] == nullptr && connections[1] != nullptr) {
            start = connections[1];
            end = static_cast<Point *>(start->getLastConnectedElement(RIGHT));
        } else if (connections[0] != nullptr && connections[1] == nullptr) {
            end = connections[0];
            start = static_cast<Point *>(connections[0]->getLastConnectedElement(LEFT));
        } else {
            end = start = nullptr;
        }
    }

    scene()->removeItem(this);

    return {start, end};
}
