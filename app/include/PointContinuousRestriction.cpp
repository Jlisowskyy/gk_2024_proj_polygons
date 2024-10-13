//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/Restrictions.h"
#include "Restrictions/PointContinuousRestriction.h"

bool PointContinuousRestriction::applyRestriction() {
    return false;
}

std::string PointContinuousRestriction::getIconName() {
    return PointIconRestrictionPath("continuous");
}
