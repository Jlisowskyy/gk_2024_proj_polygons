//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Edge.h"
#include "../Constants.h"
#include "DrawingWidget.h"

/* external includes */
#include <QPen>
#include <QDebug>
#include <QPainter>


Edge::Edge(Point *start, Point *end, DrawingWidget *drawingWidget) : QGraphicsLineItem(
        QLineF(start->getPositionOnPainter(),
               end->getPositionOnPainter())),
                                                                     IConnectableElement<Point>(
                                                                             reinterpret_cast<void *>(this)),
                                                                     IEdgePolygonObject(this),
                                                                     m_drawingWidget(drawingWidget) {
    Q_ASSERT(start != nullptr && end != nullptr);

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
