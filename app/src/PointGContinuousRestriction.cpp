//
// Created by Jlisowskyy on 21/10/24.
//

/* internal includes */
#include "../include/Restrictions/PointGContinuousRestriction.h"
#include "../include/Restrictions/Restrictions.h"

bool PointGContinuousRestriction::applyRestriction() {
    return false;
}

bool PointGContinuousRestriction::isRestrictionPreserved() {
    return true;
}

QPointF PointGContinuousRestriction::tryToPreserveRestriction(size_t direction, QPointF dxdy) {
    return {0, 0};
}

std::string PointGContinuousRestriction::getIconName() {
    return PointIconRestrictionPath("g_continuous");
}
