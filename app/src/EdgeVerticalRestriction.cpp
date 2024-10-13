//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/EdgeVerticalRestriction.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/Restrictions/Restrictions.h"

/* external includes */
#include <array>
#include <string>


bool EdgeVerticalRestriction::applyRestriction() {
    if (validateNoDoubleVerticalRestriction()) {
        return true;
    }

    Point *pointLeft = m_edge->getConnectedElement(LEFT);
    Point *pointRight = m_edge->getConnectedElement(RIGHT);

    auto posRight = pointRight->getPositionOnPainter();
    posRight.setX(pointLeft->getPositionOnPainter().x());

    pointRight->setPos(posRight);

    return false;
}

std::string EdgeVerticalRestriction::getIconName() {
    return EdgeRestrictionIconPath("vertical");
}

bool EdgeVerticalRestriction::validateNoDoubleVerticalRestriction() {
    std::array<Edge *, MAX_CONNECTIONS> arr{};

    _gatherNeighborEdges(arr);

    for (Edge *edge: arr) {
        if (edge != nullptr && dynamic_cast<EdgeVerticalRestriction *>(edge->getRestriction()) != nullptr) {
            return true;
        }
    }

    return false;
}
