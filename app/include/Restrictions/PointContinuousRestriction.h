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
protected:
    PointContinuousRestriction(Point *point, qreal coef);

    ~PointContinuousRestriction() override = default;

public:
    // ------------------------------
    // Abstract methods override
    // ------------------------------

    bool applyRestriction() final;

    bool isRestrictionPreserved() final;

    QPointF tryToPreserveRestriction(size_t direction, QPointF dxdy) final;

    virtual bool tryToPropagateControlPointChange(size_t direction);
    
    // ------------------------------
    // protected methods
    // ------------------------------
protected:
    QPointF _processDirectionBezier(size_t direction);

    // ------------------------------
    // Class fields
    // ------------------------------

    qreal m_coef;
};


#endif //APP_POINTCONTINUOUSRESTRICTION_H
