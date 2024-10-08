//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Edge.h"

/* external includes */
#include <QPen>


Edge::Edge(Point *start, Point *end) :
        QGraphicsLineItem(QLineF(start->rect().center(), end->rect().center())),
        m_start(start),
        m_end(end) {
    QPen pen(Qt::black);
    pen.setWidth(LINE_WIDTH);
    setPen(pen);

    setFlags(flags() | QGraphicsItem::ItemIsSelectable); // Removed ItemIsMovable
}
