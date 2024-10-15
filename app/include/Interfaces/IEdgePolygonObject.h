//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_IEDGEPOLYGONOBJECT_H
#define APP_IEDGEPOLYGONOBJECT_H

/* internal includes */
#include "IPolygonObject.h"

/* Forward declaration */
class Edge;

class DrawingWidget;

class Point;

class IEdgePolygonObject : public IPolygonObject {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit IEdgePolygonObject(Edge *edge, Polygon *polygon) : IPolygonObject(polygon), m_edge(edge) {}

    ~IEdgePolygonObject() override = default;

    // ------------------------------
    // Abstract methods overrides
    // ------------------------------

    std::tuple<Point *, Point *> remove(bool isFullPolygon, DrawingWidget *painter) final;

    // ------------------------------
    // Class fields
    // ------------------------------

    Edge *m_edge;
};


#endif //APP_IEDGEPOLYGONOBJECT_H
