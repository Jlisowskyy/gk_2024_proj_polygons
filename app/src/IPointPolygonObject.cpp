//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Interfaces/IPointPolygonObject.h"
#include "../include/Constants.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/DrawingWidget.h"

/* external includes */
#include <QGraphicsScene>


std::tuple<Point *, Point *> IPointPolygonObject::remove(const bool isFullPolygon, DrawingWidget *const painter) {
    Point *connections[MAX_CONNECTIONS]{};

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
    IPolygonObject::_addEdgeIfNotTriangle(connections, isFullPolygon, painter);

    /* Prepare new start and end */
    auto rv = IPolygonObject::_prepareNewAttachmentPoints(connections, isFullPolygon);

    m_point->scene()->removeItem(m_point);

    return rv;
}
