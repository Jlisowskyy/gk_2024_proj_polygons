//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_POINTCONTINUOUSRESTRICTION_H
#define APP_POINTCONTINUOUSRESTRICTION_H

/* internal includes */
#include "PointRestriction.h"

/* external includes */

/* Forward declarations */
class EdgeBezierRestriction;

class PointContinuousRestriction : public PointRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    using PointRestriction::PointRestriction;

    ~PointContinuousRestriction() override = default;

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

    QPointF _processDirectionBezier(size_t direction, QPointF dxdy, EdgeBezierRestriction *bezier);
};


#endif //APP_POINTCONTINUOUSRESTRICTION_H
