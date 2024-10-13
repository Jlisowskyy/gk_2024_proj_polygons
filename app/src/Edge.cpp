//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Edge.h"
#include "Constants.h"
#include "Painter.h"

/* external includes */
#include <QPen>
#include <QDebug>


Edge::Edge(Point *start, Point *end) : QGraphicsLineItem(QLineF(start->getPositionOnPainter(),
                                                                end->getPositionOnPainter())) {
    QPen pen(DEFAULT_COLOR);
    pen.setWidth(DEFAULT_EDGE_WIDTH);
    setPen(pen);

    /* Edges should be displayed under points */
    setZValue(0);

    setFlags(flags() | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsScenePositionChanges);

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
        default:
            return QGraphicsLineItem::itemChange(change, value);
    }
}

QVariant Edge::_onSelectionChange(const QVariant &value) {
    QPen pen(isSelected() ? SELECTED_COLOR : DEFAULT_COLOR);
    pen.setWidth(isSelected() ? SELECTED_EDGE_WIDTH : DEFAULT_EDGE_WIDTH);
    setPen(pen);

    return value;
}

QVariant Edge::_onPositionChange(const QVariant &value) {
    return value;
}

QVariant Edge::_onPositionChanged(const QVariant &value) {
    const double leftRadius = getConnectedElement(LEFT)->getRadius();
    const double rightRadius = getConnectedElement(RIGHT)->getRadius();

    m_isUpdating = true;
    getConnectedElement(LEFT)->setPos(line().p1() + value.toPointF() - QPointF(leftRadius, leftRadius));
    getConnectedElement(RIGHT)->setPos(line().p2() + value.toPointF() - QPointF(rightRadius, rightRadius));
    m_isUpdating = false;

    return value;
}

void Edge::repositionByPoints() {
    if (!m_isUpdating) {
        setLine(QLineF(getConnectedElement(LEFT)->getPositionOnPainter(),
                       getConnectedElement(RIGHT)->getPositionOnPainter()));
        setPos({0, 0});
    }
}

std::tuple<Point *, Point *> Edge::remove(bool isFullPolygon, Painter *painter) {
}
