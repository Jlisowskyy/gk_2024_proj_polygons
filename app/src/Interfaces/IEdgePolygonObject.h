//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_IEDGEPOLYGONOBJECT_H
#define APP_IEDGEPOLYGONOBJECT_H

/* internal includes */
#include "IPolygonObject.h"

/* Forward declaration */
class Edge;

class Painter;

class Point;

class IEdgePolygonObject : public IPolygonObject {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit IEdgePolygonObject(Edge *edge) : m_edge(edge) {}

    ~IEdgePolygonObject() override = default;

    // ------------------------------
    // Abstract methods overrides
    // ------------------------------

    std::tuple<Point *, Point *> remove(bool isFullPolygon, Painter *painter) final;

    // ------------------------------
    // Class fields
    // ------------------------------

    Edge *m_edge;
};


#endif //APP_IEDGEPOLYGONOBJECT_H
