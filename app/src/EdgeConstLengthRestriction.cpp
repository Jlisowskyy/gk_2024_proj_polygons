//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/Restrictions.h"
#include "../include/Restrictions/EdgeConstLengthRestriction.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/LengthDialog.h"

/* external includes */
#include <cmath>

bool EdgeConstLengthRestriction::applyRestriction() {
    LengthDialog dialog(nullptr, m_edge->getLength());

    if (dialog.exec() == QDialog::Accepted) {
        m_length = dialog.getLength();
        return false;
    } else {
        return true;
    }

    return false;
}

std::string EdgeConstLengthRestriction::getIconName() {
    return EdgeRestrictionIconPath("const_length");
}

EdgeConstLengthRestriction::EdgeConstLengthRestriction(Edge *edge) : EdgeRestriction(edge){

}

QPointF EdgeConstLengthRestriction::tryToPreserveRestriction(size_t direction, QPointF dxdy) {
    return {0, 0};
}

bool EdgeConstLengthRestriction::isRestrictionPreserved() {
    static constexpr double PRECISION_LIMIT = 0.5;

    return std::abs(m_edge->getLength() - m_length) <= PRECISION_LIMIT;
}
