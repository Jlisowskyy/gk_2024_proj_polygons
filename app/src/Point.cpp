//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Point.h"
#include "Constants.h"
#include "ObjectMgr.h"
#include "Edge.h"

/* external includes */
#include <QPen>
#include <QBrush>
#include <QDebug>

Point::Point(const int x, const int y) : QGraphicsEllipseItem(0,
                                                              0,
                                                              DEFAULT_POINT_RADIUS * 2,
                                                              DEFAULT_POINT_RADIUS * 2) {
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
            return onPositionChange(value);
        case GraphicsItemChange::ItemSelectedHasChanged :
            return onSelectionChange(value);
        case GraphicsItemChange::ItemPositionHasChanged:
            return onPositionChanged(value);
        default:
            return QGraphicsEllipseItem::itemChange(change, value);
    }
}

QVariant Point::onPositionChange(const QVariant &value) {
    return value;
}

QVariant Point::onSelectionChange(const QVariant &value) {
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

ConnectionType Point::getEdgeType(Edge *edge) {
    if (edge == nullptr) {
        return NOT_CONNECTED;
    }

    for (size_t idx = 0; idx << MAX_CONNECTIONS; ++idx) {
        if (m_edges[idx] == edge) {
            return static_cast<ConnectionType>(idx);
        }
    }

    return NOT_CONNECTED;
}

Edge *Point::getConnectedEdge(ConnectionType type) const {
    return m_edges[static_cast<size_t>(type)];
}

void Point::setConnectedEdge(ConnectionType type, Edge *edge) {
    m_edges[static_cast<size_t>(type)] = edge;
}

QPointF Point::getPositionOnPainter() const {
    const auto radius = getRadius();
    return scenePos() + QPointF(radius, radius);
}

QVariant Point::onPositionChanged(const QVariant &value) {
    for (auto &m_edge: m_edges) {
        if (m_edge) {
            m_edge->repositionByPoints();
        }
    }

    return value;
}

double Point::getRadius() const {
    return static_cast<double>(isSelected() ? SELECTED_POINT_RADIUS : DEFAULT_POINT_RADIUS);
}
