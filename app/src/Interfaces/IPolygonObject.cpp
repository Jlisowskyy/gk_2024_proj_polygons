//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "IPolygonObject.h"
#include "../GraphicObjects/Point.h"
#include "../GraphicObjects/Painter.h"

void IPolygonObject::_addEdgeIfNotTriangle(Point **connections, const bool isFullPolygon, Painter *const painter) {
    if (connections[0] != nullptr &&
        connections[1] != nullptr &&
        !(isFullPolygon &&
          static_cast<void *>(connections[1]->getConnectedElement(RIGHT)) != static_cast<void *>(connections[0]))) {

        Edge *edge = painter->addEdge(connections[0], connections[1]);
        connections[0]->setConnectedElement(RIGHT, edge);
        connections[1]->setConnectedElement(LEFT, edge);
    }
}

std::tuple<Point *, Point *> IPolygonObject::_prepareNewAttachmentPoints(Point **connections, bool isFullPolygon) {
    Point *start{};
    Point *end{};

    if (isFullPolygon) {
        Q_ASSERT(connections[LEFT] != nullptr && connections[RIGHT] != nullptr);

        start = connections[RIGHT];
        end = connections[LEFT];
    } else {
        start = connections[LEFT] == nullptr ? connections[RIGHT]
                                             : reinterpret_cast<Point *>(connections[LEFT]->getLastConnectedElement(
                        LEFT));

        end = connections[RIGHT] == nullptr ? connections[LEFT]
                                            : reinterpret_cast<Point *>(connections[RIGHT]->getLastConnectedElement(
                        RIGHT));
    }

    return {start, end};
}
