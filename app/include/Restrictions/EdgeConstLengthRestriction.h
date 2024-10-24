//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_EDGECONSTLENGTHRESTRICTION_H
#define APP_EDGECONSTLENGTHRESTRICTION_H

/* internal includes */
#include "EdgeRestriction.h"

/* external includes */

class EdgeConstLengthRestriction : public EdgeRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit EdgeConstLengthRestriction(Edge *edge);

    explicit EdgeConstLengthRestriction(Edge *edge, qreal length);

    ~EdgeConstLengthRestriction() override = default;

    // ------------------------------
    // Abstract methods override
    // ------------------------------

    bool applyRestriction() final;

    bool isRestrictionPreserved() final;

    QPointF tryToPreserveRestriction(size_t direction, QPointF dxdy) final;

    std::string getIconName() override;

    // ------------------------------
    // Protected methods
    // ------------------------------
protected:

    bool _isLegalUsage();



    // ------------------------------
    // Class fields
    // ------------------------------

    double m_length{};
};


#endif //APP_EDGECONSTLENGTHRESTRICTION_H
