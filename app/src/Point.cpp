//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Point.h"

/* external includes */
#include <QPen>
#include <QBrush>

Point::Point(const int x, const int y): QGraphicsEllipseItem(x - POINT_RADIUS,
                                                             y - POINT_RADIUS,
                                                             POINT_RADIUS * 2,
                                                             POINT_RADIUS * 2) {
    setFlags(flags() | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setPen(QPen(Qt::black));
    setBrush(QBrush(Qt::black));
}

QPointF Point::getPositionOnPainter() const {
    return rect().center();
}
