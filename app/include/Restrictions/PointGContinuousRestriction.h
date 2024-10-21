//
// Created by Jlisowskyy on 21/10/24.
//

#ifndef APP_POINTGCONTINUOUSRESTRICTION_H
#define APP_POINTGCONTINUOUSRESTRICTION_H


/* internal includes */
#include "PointRestriction.h"

/* external includes */

class PointGContinuousRestriction : public PointRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    using PointRestriction::PointRestriction;

    ~PointGContinuousRestriction() override = default;

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

};


#endif //APP_POINTGCONTINUOUSRESTRICTION_H
