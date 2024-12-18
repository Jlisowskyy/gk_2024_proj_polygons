//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_IPOINTPOLYGONOBJECT_H
#define APP_IPOINTPOLYGONOBJECT_H

/* internal includes */
#include <functional>
#include "IPolygonObject.h"

/* Forward declaration */
class Point;

class IPointPolygonObject : public IPolygonObject {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit IPointPolygonObject(Point *point, Polygon *polygon) : IPolygonObject(polygon), m_point(point) {}

    ~IPointPolygonObject() override = default;

    // ------------------------------
    // Abstract methods overrides
    // ------------------------------

    std::tuple<Point *, Point *> remove(bool isFullPolygon, DrawingWidget *painter) final;

    virtual bool
    tryToPreserveRestrictions(const QPointF point, const size_t direction, Point *blockPoint, const bool dryRun,
                              std::function<bool()> func) = 0;

    // ------------------------------
    // Class fields
    // ------------------------------

    Point *m_point;
};


#endif //APP_IPOINTPOLYGONOBJECT_H
