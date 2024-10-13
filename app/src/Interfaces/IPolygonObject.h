
//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_IPOLYGONOBJECT_H
#define APP_IPOLYGONOBJECT_H

/* external includes */
#include <tuple>

/* Forward declaration */
class Point;

class Painter;

class IPolygonObject {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    IPolygonObject() = default;

    virtual ~IPolygonObject() = default;

    // ------------------------------
    // Abstract methods
    // ------------------------------

    virtual std::tuple<Point *, Point *> remove(bool isFullPolygon, Painter *painter) = 0;

    // ------------------------------
    // Protected methods
    // ------------------------------
protected:

    // ------------------------------
    // Static methods
    // ------------------------------

    static void _addEdgeIfNotTriangle(Point **connections, bool isFullPolygon, Painter *painter);

    [[nodiscard]] static std::tuple<Point *, Point *>
    _prepareNewAttachmentPoints(Point **connections, bool isFullPolygon);
};

#endif //APP_IPOLYGONOBJECT_H
