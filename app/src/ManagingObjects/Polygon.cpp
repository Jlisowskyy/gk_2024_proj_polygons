//
// Created by Jlisowskyy on 09/10/24.
//

/* internal includes */
#include "Polygon.h"
#include "../Interfaces/IPolygonObject.h"

/* external includes */

Polygon::Polygon(QObject *parent) : QObject(parent) {
    Q_ASSERT(parent != nullptr);
}

void Polygon::setupMgr(Painter *painter) {
    Q_ASSERT(painter != nullptr);
    Q_ASSERT(m_painter == nullptr);
    m_painter = painter;

    setIsAddingVertices(true);
    addPoint(3 * 50, 3 * 50);
    addPoint(3 * 100, 3 * 50);
    addPoint(3 * 100, 3 * 100);
    setIsAddingVertices(false);
}

void Polygon::clearItems() {
    m_painter->clearContent();

    m_startingPoint = m_endingPoint = nullptr;
}

bool Polygon::getIsAddingVertices() const {
    return m_isAddingVertices;
}

void Polygon::setIsAddingVertices(const bool value) {
    m_isAddingVertices = value;
    m_painter->updateInteractivity();
}

bool Polygon::isFullPolygon() const {
    return m_startingPoint != nullptr && m_endingPoint != nullptr &&
           m_endingPoint->getConnectedElement(RIGHT) != nullptr;
}

Point *Polygon::_findPointSpot(const int x, const int y) const {
    if (m_endingPoint == nullptr || m_startingPoint->getConnectedElement(RIGHT) == nullptr
        || m_endingPoint->getConnectedElement(LEFT)->getConnectedElement(LEFT) == m_startingPoint) {
        return m_painter->addPoint(x, y);
    }

    const int xDist = x - m_startingPoint->getPositionOnPainter().toPoint().x();
    const int yDist = y - m_startingPoint->getPositionOnPainter().toPoint().y();
    const bool isInsideHitBox = xDist * xDist + yDist * yDist <= FINAL_POINT_HIT_BOX_SIZE * FINAL_POINT_HIT_BOX_SIZE;

    return isInsideHitBox ? nullptr : m_painter->addPoint(x, y);
}

void Polygon::addPoint(const int x, const int y) {
    if (!getIsAddingVertices() || isFullPolygon()) {
        return;
    }

    auto *point = _findPointSpot(x, y);

    if (point == nullptr) {
        auto *edge = m_painter->addEdge(m_endingPoint, m_startingPoint);

        m_endingPoint->setConnectedElement(RIGHT, edge);
        m_startingPoint->setConnectedElement(LEFT, edge);
    } else {
        if (m_startingPoint == nullptr) {
            m_startingPoint = m_endingPoint = point;
        } else {
            auto *edge = m_painter->addEdge(m_endingPoint, point);

            m_endingPoint->setConnectedElement(RIGHT, edge);
            point->setConnectedElement(LEFT, edge);

            m_endingPoint = point;
        }
    }
}

void Polygon::removeSelection() {
    QGraphicsItem *selectedItem = m_painter->getSelectedItem();

    if (selectedItem == nullptr) {
        return;
    }

    const bool bIsFoolPolygon = isFullPolygon();
    m_painter->clearSelection();

    auto *pObject = dynamic_cast<IPolygonObject *>(selectedItem);
    Q_ASSERT(pObject != nullptr);

    const auto [p1, p2] = pObject->remove(bIsFoolPolygon, m_painter);
    m_startingPoint = p1;
    m_endingPoint = p2;
}
