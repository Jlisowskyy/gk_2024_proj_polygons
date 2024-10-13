//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "IEdgePolygonObject.h"
#include "../Constants.h"
#include "../GraphicObjects/Edge.h"
#include "../GraphicObjects/Point.h"
#include "../GraphicObjects/Painter.h"

/* external includes */
#include <QGraphicsScene>

std::tuple<Point *, Point *> IEdgePolygonObject::remove(bool isFullPolygon, Painter *painter) {
    Point *connections[MAX_CONNECTIONS]{};

    /* Gather connections */
    for (size_t direction = 0; direction < MAX_CONNECTIONS; ++direction) {
        if (Point *itemToRemove1 = m_edge->getConnectedElement(direction); itemToRemove1 != nullptr) {
            if (Edge *itemToRemove2 = itemToRemove1->getConnectedElement(direction); itemToRemove2 != nullptr) {
                connections[direction] = itemToRemove2->getConnectedElement(direction);
                Q_ASSERT(connections[direction] != nullptr);
                connections[direction]->setConnectedElement(SwapDirection(direction), nullptr);

                m_edge->scene()->removeItem(itemToRemove2);
            }

            m_edge->scene()->removeItem(itemToRemove1);
        }
    }

    /* Add edge except triangle case */
    IPolygonObject::_addEdgeIfNotTriangle(connections, isFullPolygon, painter);

    /* Prepare new start and end */
    auto rv = IPolygonObject::_prepareNewAttachmentPoints(connections, isFullPolygon);

    m_edge->scene()->removeItem(m_edge);

    return rv;
}
