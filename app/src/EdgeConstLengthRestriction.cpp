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
#include <QLineF>

bool EdgeConstLengthRestriction::applyRestriction() {
    static constexpr double PRECISION_LIMIT = 0.2;

    if (m_length == 0) {
        LengthDialog dialog(nullptr, m_edge->getLength());

        if (dialog.exec() == QDialog::Accepted) {
            m_length = dialog.getLength();
        } else {
            return true;
        }
    }

    if (std::abs(m_length - m_edge->getLength()) > PRECISION_LIMIT) {
        if (!_isLegalUsage()) {
            return true;
        }

        Point *point = m_edge->getConnectedElement(LEFT);
        Q_ASSERT(point);

        const QPointF dxdy = tryToPreserveRestriction(LEFT, QPointF(0, 0));
        point->setPositionOnPainter(point->getPositionOnPainter() + dxdy);
    }

    return false;
}

std::string EdgeConstLengthRestriction::getIconName() {
    return EdgeRestrictionIconPath("const_length");
}

EdgeConstLengthRestriction::EdgeConstLengthRestriction(Edge *edge) : EdgeRestriction(edge) {

}

EdgeConstLengthRestriction::EdgeConstLengthRestriction(Edge *edge, qreal length) : EdgeRestriction(edge),
                                                                                   m_length(length) {

}


QPointF EdgeConstLengthRestriction::tryToPreserveRestriction(size_t direction, [[maybe_unused]] const QPointF dxdy) {
    Point *point1 = direction == LEFT ? m_edge->getConnectedElement(RIGHT) : m_edge->getConnectedElement(LEFT);
    Point *point2 = m_edge->getConnectedElement(direction);

    Q_ASSERT(point1 && point2);

    QPointF pos1 = point1->getPositionOnPainter();
    QPointF pos2 = point2->getPositionOnPainter();

    QLineF line(pos1, pos2);
    line.setLength(m_length);

    return line.p2() - pos2;
}


bool EdgeConstLengthRestriction::isRestrictionPreserved() {
    static constexpr double PRECISION_LIMIT = 0.5;

    return std::abs(m_edge->getLength() - m_length) <= PRECISION_LIMIT;
}

bool EdgeConstLengthRestriction::_isLegalUsage() {
    Point *point = m_edge->getConnectedElement(LEFT);
    Q_ASSERT(point);

    bool isThereEdgeWithoutConstLenRestriction = false;
    point->iterateEdges([&isThereEdgeWithoutConstLenRestriction, this](Edge *edge) {
        if (m_edge != edge && dynamic_cast<EdgeConstLengthRestriction *>(edge->getRestriction()) == nullptr) {
            isThereEdgeWithoutConstLenRestriction = true;
        }
    });

    return isThereEdgeWithoutConstLenRestriction;
}
