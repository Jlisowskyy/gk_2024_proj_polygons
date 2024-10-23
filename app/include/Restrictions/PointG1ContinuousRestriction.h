//
// Created by Jlisowskyy on 10/22/24.
//

#ifndef POINTG1CONTINUOUSRESTRICTION_H
#define POINTG1CONTINUOUSRESTRICTION_H

/* internal includes */
#include "PointContinuousRestriction.h"

/* external includes */

class PointG1ContinuousRestriction : public PointContinuousRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:
    explicit PointG1ContinuousRestriction(Point *point): PointContinuousRestriction(point, 0) {
    }

    ~PointG1ContinuousRestriction() override = default;

    std::string getIconName() override {
        return PointIconRestrictionPath("g1_continuous");
    }
};

#endif //POINTG1CONTINUOUSRESTRICTION_H
