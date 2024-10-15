//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/EdgeRestriction.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/Edge.h"

void EdgeRestriction::_gatherNeighborEdges(std::array<Edge *, MAX_CONNECTIONS> &array) {
    for (size_t direction = 0; direction < MAX_CONNECTIONS; ++direction) {
        if (Point *point = m_edge->getConnectedElement(direction); point != nullptr) {
            array[direction] = point->getConnectedElement(direction);
        }
    }
}

QPointF EdgeRestriction::getIconPosition() {
    const QPointF midPoint = m_edge->getMidPoint();
    const QPointF startPoint = m_edge->getConnectedElement(LEFT)->getPositionOnPainter();
    const QPointF endPoint = m_edge->getConnectedElement(RIGHT)->getPositionOnPainter();

    QPointF edgeVector = endPoint - startPoint;

    qreal length = QLineF(startPoint, endPoint).length();
    if (qFuzzyIsNull(length)) {
        return midPoint;
    }
    edgeVector /= length;
    QPointF perpVector(-edgeVector.y(), edgeVector.x());
    const qreal offsetDistance = 20.0;
    QPointF iconPosition = midPoint + perpVector * offsetDistance;

    return iconPosition;
}

void EdgeRestriction::onRestrictionDelete() {
    m_edge->cleanRestriction();
}
