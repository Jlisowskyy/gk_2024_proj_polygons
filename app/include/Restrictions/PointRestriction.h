//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_POINTRESTRICTION_H
#define APP_POINTRESTRICTION_H

/* internal includes */
#include "ObjectRestriction.h"

/* external includes */
#include <Qt>

/* Forward declaration */
class Point;

class PointRestriction : public ObjectRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit PointRestriction(Point *point) : m_point(point) {
        Q_ASSERT(point != nullptr);
    };

    ~PointRestriction() override = default;

    // ------------------------------
    // protected methods
    // ------------------------------
protected:

    void onRestrictionDelete() override;

    QPoint getIconPosition() override;

    // ------------------------------
    // Class fields
    // ------------------------------
protected:

    Point *m_point{};
};


#endif //APP_POINTRESTRICTION_H
