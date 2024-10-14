//
// Created by Jlisowskyy on 14/10/24.
//

#ifndef APP_EDGEBEZIERRESTRICTION_H
#define APP_EDGEBEZIERRESTRICTION_H

/* internal includes */
#include "EdgeRestriction.h"

/* external includes */

class EdgeBezierRestriction : public EdgeRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    using EdgeRestriction::EdgeRestriction;

    ~EdgeBezierRestriction() override = default;

    // ------------------------------
    // Abstract methods override
    // ------------------------------

    bool applyRestriction() final;

    std::string getIconName() override;

    // ------------------------------
    // protected methods
    // ------------------------------
protected:

};

#endif //APP_EDGEBEZIERRESTRICTION_H
