//
// Created by Jlisowskyy on 14/10/24.
//

/* internal includes */
#include "../include/Restrictions/EdgeBezierRestriction.h"
#include "../include/Restrictions/Restrictions.h"

/* external includes */

bool EdgeBezierRestriction::applyRestriction() {
    return false;
}

std::string EdgeBezierRestriction::getIconName() {
    return EdgeRestrictionIconPath("bezier");
}
