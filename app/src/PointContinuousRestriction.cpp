//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/Restrictions.h"
#include "../include/Restrictions/PointContinuousRestriction.h"

bool PointContinuousRestriction::applyRestriction() {
    return false;
}

std::string PointContinuousRestriction::getIconName() {
    return PointIconRestrictionPath("continuous");
}

bool PointContinuousRestriction::isRestrictionPreserved() {
    return true;
}

QPointF
PointContinuousRestriction::tryToPreserveRestriction([[maybe_unused]] size_t direction, [[maybe_unused]] QPointF dxdy) {
    return {0, 0};
}
