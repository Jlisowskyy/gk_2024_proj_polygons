//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "IPointPolygonObject.h"
#include "../Constants.h"
#include "../GraphicObjects/Edge.h"
#include "../GraphicObjects/Point.h"
#include "../GraphicObjects/Painter.h"

/* external includes */
#include <QGraphicsScene>


std::tuple<Point *, Point *> IPointPolygonObject::remove(const bool isFullPolygon, Painter *const painter) {
    Point *connections[MAX_CONNECTIONS]{};
    Point *start{};
    Point *end{};

    /* Gather connections */
    for (size_t direction = 0; direction < MAX_CONNECTIONS; ++direction) {
        if (Edge *itemToRemove = m_point->getConnectedElement(direction); itemToRemove != nullptr) {
            connections[direction] = itemToRemove->getConnectedElement(direction);
            Q_ASSERT(connections[direction] != nullptr);

            connections[direction]->setConnectedElement(SwapDirection(direction), nullptr);

            m_point->scene()->removeItem(itemToRemove);
        }
    }

    /* Add edge except triangle case */
    if (connections[LEFT] != nullptr &&
        connections[RIGHT] != nullptr &&
        !(isFullPolygon &&
          static_cast<void *>(connections[1]->getConnectedElement(RIGHT)) != static_cast<void *>(connections[0]))) {

        Edge *edge = painter->addEdge(connections[LEFT], connections[RIGHT]);
        connections[LEFT]->setConnectedElement(RIGHT, edge);
        connections[RIGHT]->setConnectedElement(LEFT, edge);
    }

    /* Prepare new start and end */
    if (isFullPolygon) {
        Q_ASSERT(connections[LEFT] != nullptr && connections[RIGHT] != nullptr);

        start = connections[RIGHT];
        end = connections[LEFT];
    } else {
        start = connections[LEFT] == nullptr ? connections[RIGHT]
                                             : reinterpret_cast<Point *>(connections[LEFT]->getLastConnectedElement(LEFT));

        end = connections[RIGHT] == nullptr ? connections[LEFT]
                                            : reinterpret_cast<Point *>(connections[RIGHT]->getLastConnectedElement(RIGHT));
    }

    m_point->scene()->removeItem(m_point);

    return {start, end};
}
