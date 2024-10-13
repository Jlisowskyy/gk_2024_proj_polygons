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
    if (connections[0] != nullptr &&
        connections[1] != nullptr &&
        !(isFullPolygon &&
          static_cast<void *>(connections[1]->getConnectedElement(RIGHT)) != static_cast<void *>(connections[0]))) {

        Edge *edge = painter->addEdge(connections[0], connections[1]);
        connections[0]->setConnectedElement(RIGHT, edge);
        connections[1]->setConnectedElement(LEFT, edge);
    }

    /* Prepare new start and end */
    if (isFullPolygon) {
        Q_ASSERT(connections[0] != nullptr && connections[1] != nullptr);

        start = connections[1];
        end = connections[0];
    } else {
        if (connections[0] == nullptr && connections[1] != nullptr) {
            start = connections[1];
            end = static_cast<Point *>(start->getLastConnectedElement(RIGHT));
        } else if (connections[0] != nullptr && connections[1] == nullptr) {
            end = connections[0];
            start = static_cast<Point *>(connections[0]->getLastConnectedElement(LEFT));
        } else {
            end = start = nullptr;
        }
    }

    m_point->scene()->removeItem(m_point);

    return {start, end};
}
