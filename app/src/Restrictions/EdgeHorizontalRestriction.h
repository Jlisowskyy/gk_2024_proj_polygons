//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_EDGEHORIZONTALRESTRICTION_H
#define APP_EDGEHORIZONTALRESTRICTION_H

/* internal includes */
#include "EdgeRestriction.h"

class EdgeHorizontalRestriction : public EdgeRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    using EdgeRestriction::EdgeRestriction;

    ~EdgeHorizontalRestriction() override = default;

    // ------------------------------
    // Abstract methods
    // ------------------------------

    bool applyRestriction() final;

};


#endif //APP_EDGEHORIZONTALRESTRICTION_H
