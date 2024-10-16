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

    /* TODO: validate there is no all const length constraints */

    if (dialog.exec() == QDialog::Accepted) {
        m_length = dialog.getLength();

        if (m_length != m_edge->getLength()) {
            Point *point = m_edge->getConnectedElement(LEFT);
            Q_ASSERT(point);



            /* TODO : HANDLE THAT */
        }

        return false;
    }

    return true;
}

std::string EdgeConstLengthRestriction::getIconName() {
    return EdgeRestrictionIconPath("const_length");
}

EdgeConstLengthRestriction::EdgeConstLengthRestriction(Edge *edge) : EdgeRestriction(edge) {

}

QPointF EdgeConstLengthRestriction::tryToPreserveRestriction([[maybe_unused]] size_t direction, const QPointF dxdy) {
    return dxdy;
}


bool EdgeConstLengthRestriction::isRestrictionPreserved() {
    static constexpr double PRECISION_LIMIT = 0.5;

    return std::abs(m_edge->getLength() - m_length) <= PRECISION_LIMIT;
}
