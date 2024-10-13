//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_EDGEHORIZONTALRESTRICTION_H
#define APP_EDGEHORIZONTALRESTRICTION_H

/* internal includes */
#include "EdgeRestriction.h"

/* external includes */

class EdgeHorizontalRestriction : public EdgeRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    using EdgeRestriction::EdgeRestriction;

    ~EdgeHorizontalRestriction() override = default;

    // ------------------------------
    // Abstract methods override
    // ------------------------------

    bool applyRestriction() final;

    std::string getIconName() override;

    // ------------------------------
    // protected methods
    // ------------------------------
protected:

    bool validateNoDoubleHorizontalRestriction();

};


#endif //APP_EDGEHORIZONTALRESTRICTION_H
