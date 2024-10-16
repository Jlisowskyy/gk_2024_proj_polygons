//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Interfaces/IEdgePolygonObject.h"
#include "../include/Constants.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/DrawingWidget.h"
#include "../include/Restrictions/ObjectRestriction.h"

/* external includes */
#include <QGraphicsScene>

std::tuple<Point *, Point *> IEdgePolygonObject::remove(bool isFullPolygon, DrawingWidget *painter) {
    Point *connections[MAX_CONNECTIONS]{};

    /* Gather connections */
    for (size_t direction = 0; direction < MAX_CONNECTIONS; ++direction) {
        if (Point *itemToRemove1 = m_edge->getConnectedElement(direction); itemToRemove1 != nullptr) {
            if (Edge *itemToRemove2 = itemToRemove1->getConnectedElement(direction); itemToRemove2 != nullptr) {
                connections[direction] = itemToRemove2->getConnectedElement(direction);
                Q_ASSERT(connections[direction] != nullptr);
                connections[direction]->setConnectedElement(swapDirection(direction), nullptr);

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

bool IEdgePolygonObject::isRestrictionPreserved() {
    return m_restriction == nullptr || m_restriction->isRestrictionPreserved();
}
