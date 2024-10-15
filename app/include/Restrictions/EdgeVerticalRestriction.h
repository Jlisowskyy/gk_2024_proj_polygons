//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_EDGEVERTICALRESTRICTION_H
#define APP_EDGEVERTICALRESTRICTION_H

/* internal includes */
#include "EdgeRestriction.h"

/* external includes */

class EdgeVerticalRestriction : public EdgeRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    using EdgeRestriction::EdgeRestriction;

    ~EdgeVerticalRestriction() override = default;

    // ------------------------------
    // Abstract methods override
    // ------------------------------

    bool applyRestriction() final;

    bool isRestrictionPreserved() final;

    QPointF tryToPreserveRestriction(size_t direction, QPointF dxdy) final;

    std::string getIconName() override;

    // ------------------------------
    // protected methods
    // ------------------------------
protected:

    bool validateNoDoubleVerticalRestriction();
};


#endif //APP_EDGEVERTICALRESTRICTION_H
