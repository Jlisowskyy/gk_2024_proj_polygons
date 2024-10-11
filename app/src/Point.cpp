//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Point.h"
#include "Constants.h"
#include "ObjectMgr.h"
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
        case GraphicsItemChange::ItemSelectedHasChanged :
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
    return scenePos() + QPointF(radius, radius);
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

std::tuple<Point *, Point *> Point::remove(bool isFullPolygon, Painter *painter) {
    Point *connections[MAX_CONNECTIONS];

    for (size_t idx = 0; idx < MAX_CONNECTIONS; ++idx) {
        Edge *itemToRemove = getConnectedElement(idx);

        if (itemToRemove != nullptr) {
            connections[idx] = itemToRemove->getConnectedElement(idx);

            scene()->removeItem(itemToRemove);
        }
    }

    if (connections[0] != nullptr && connections[1] != nullptr) {
        Edge *edge = painter->addEdge(connections[0], connections[1]);
        connections[0]->setConnectedElement(RIGHT, edge);
        connections[1]->setConnectedElement(LEFT, edge);
    }

    if (isFullPolygon) {
        /* triangle */
        if ()
    }

    scene()->removeItem(this);
}
