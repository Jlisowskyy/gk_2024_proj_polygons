//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/EdgeHorizontalRestriction.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/Restrictions/Restrictions.h"

/* external includes */
#include <array>
#include <string>

/**
 * @return false - success / true - failed
 */
bool EdgeHorizontalRestriction::applyRestriction() {
    if (validateNoDoubleHorizontalRestriction()) {
        return true;
    }

    Point *pointLeft = m_edge->getConnectedElement(LEFT);
    Point *pointRight = m_edge->getConnectedElement(RIGHT);

    auto posRight = pointRight->getPositionOnPainter();
    posRight.setY(pointLeft->getPositionOnPainter().y());

    pointRight->setPos(posRight);

    return false;
}

bool EdgeHorizontalRestriction::validateNoDoubleHorizontalRestriction() {
    std::array<Edge *, MAX_CONNECTIONS> arr{};

    _gatherNeighborEdges(arr);

    for (Edge *edge: arr) {
        if (edge != nullptr && dynamic_cast<EdgeHorizontalRestriction *>(edge->getRestriction()) != nullptr) {
            return true;
        }
    }

    return false;
}

std::string EdgeHorizontalRestriction::getIconName() {
    return EdgeRestrictionIconPath("horizontal");
}
