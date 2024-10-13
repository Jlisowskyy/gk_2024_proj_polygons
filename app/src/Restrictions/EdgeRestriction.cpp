//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "EdgeRestriction.h"
#include "../GraphicObjects/Point.h"
#include "../GraphicObjects/Edge.h"

void EdgeRestriction::_gatherNeighborEdges(std::array<Edge *, MAX_CONNECTIONS> &array) {
    for (size_t direction = 0; direction < MAX_CONNECTIONS; ++direction) {
        if (Point *point = m_edge->getConnectedElement(direction); point != nullptr) {
            array[direction] = point->getConnectedElement(direction);
        }
    }
}

QPoint EdgeRestriction::getIconPosition() {
    return m_edge->getMidPoint() + QPoint(20, -20);
}

void EdgeRestriction::onRestrictionDelete() {
    m_edge->cleanRestriction();
}
