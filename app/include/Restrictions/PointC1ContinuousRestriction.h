//
// Created by Jlisowskyy on 10/22/24.
//

#ifndef POINTC1CONTINUOUSRESTRICTION_H
#define POINTC1CONTINUOUSRESTRICTION_H

/* internal includes */
#include "PointContinuousRestriction.h"

/* external includes */

class PointC1ContinuousRestriction : public PointContinuousRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:
    explicit PointC1ContinuousRestriction(Point *point) : PointContinuousRestriction(point, 4.0 / 3.0) {
    }

    ~PointC1ContinuousRestriction() override = default;

    std::string getIconName() override {
        return PointIconRestrictionPath("c1_continuous");
    }
};

#endif //POINTC1CONTINUOUSRESTRICTION_H
