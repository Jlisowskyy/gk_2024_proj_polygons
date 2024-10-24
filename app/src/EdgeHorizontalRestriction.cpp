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

    auto posLeft = pointLeft->getPositionOnPainter();
    posLeft.setY(pointRight->getPositionOnPainter().y());
    pointLeft->setPositionOnPainter(posLeft);

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

QPointF
EdgeHorizontalRestriction::tryToPreserveRestriction(const size_t direction, [[maybe_unused]]  const QPointF dxdy) {
    const qreal dy = m_edge->getConnectedElement(swapDirection(direction))->getPositionOnPainter().y() -
                      m_edge->getConnectedElement(direction)->getPositionOnPainter().y();

    return {0, dy};
}

bool EdgeHorizontalRestriction::isRestrictionPreserved() {
    Point *pointLeft = m_edge->getConnectedElement(LEFT);
    Point *pointRight = m_edge->getConnectedElement(RIGHT);
    Q_ASSERT(pointRight && pointLeft);

    return pointRight->getPositionOnPainter().y() == pointLeft->getPositionOnPainter().y();
}
