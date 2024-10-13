//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "Restrictions.h"
#include "EdgeConstLengthRestriction.h"
#include "../GraphicObjects/Edge.h"

bool EdgeConstLengthRestriction::applyRestriction() {
    return false;
}

std::string EdgeConstLengthRestriction::getIconName() {
    return EdgeRestrictionIconPath("const_length");
}

EdgeConstLengthRestriction::EdgeConstLengthRestriction(Edge *edge) : EdgeRestriction(edge),
                                                                     m_length(edge->getLength()) {

}
