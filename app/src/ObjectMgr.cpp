//
// Created by Jlisowskyy on 09/10/24.
//

/* internal includes */
#include "ObjectMgr.h"

/* external includes */

ObjectMgr::ObjectMgr(QObject *parent) : QObject(parent) {
    Q_ASSERT(parent != nullptr);
}

void ObjectMgr::setupMgr(Painter *painter) {
    Q_ASSERT(painter != nullptr);
    Q_ASSERT(m_painter == nullptr);
    m_painter = painter;

    setIsAddingVertices(true);
    addPoint(3 * 50, 3 * 50);
    addPoint(3 * 100, 3 * 50);
    addPoint(3 * 100, 3 * 100);
    setIsAddingVertices(false);
}

void ObjectMgr::clearItems() {
    m_painter->clearContent();

    m_startingPoint = m_endingPoint = nullptr;
}

bool ObjectMgr::getIsAddingVertices() const {
    return m_isAddingVertices;
}

void ObjectMgr::setIsAddingVertices(const bool value) {
    m_isAddingVertices = value;
    m_painter->updateInteractivity();
}

bool ObjectMgr::isFullPolygon() const {
    return m_startingPoint != nullptr && m_endingPoint != nullptr &&
           m_endingPoint->getConnectedElement(RIGHT) != nullptr;
}

Point *ObjectMgr::_findPointSpot(const int x, const int y) const {
    if (m_endingPoint == nullptr || m_startingPoint->getConnectedElement(RIGHT) == nullptr
        || m_endingPoint->getConnectedElement(LEFT)->getConnectedElement(LEFT) == m_startingPoint) {
        return m_painter->addPoint(x, y);
    }

    const int xDist = x - m_startingPoint->getPositionOnPainter().toPoint().x();
    const int yDist = y - m_endingPoint->getPositionOnPainter().toPoint().y();
    const bool isInsideHitBox = xDist * xDist + yDist * yDist <= FINAL_POINT_HIT_BOX_SIZE * FINAL_POINT_HIT_BOX_SIZE;

    return isInsideHitBox ? nullptr : m_painter->addPoint(x, y);
}

void ObjectMgr::addPoint(const int x, const int y) {
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

void ObjectMgr::removeSelection() {
    QGraphicsItem *selectedItem = m_painter->getSelectedItem();

    if (selectedItem == nullptr) {
        return;
    }

    const bool bIsFoolPolygon = isFullPolygon();
    m_painter->clearSelection();
    if (auto *pEdge = dynamic_cast<Edge *>(selectedItem); pEdge != nullptr) {
        const auto [p1, p2] = pEdge->remove(bIsFoolPolygon, m_painter);
        m_startingPoint = p1;
        m_endingPoint = p2;
    } else if (auto *pPoint = dynamic_cast<Point *>(selectedItem); pPoint != nullptr) {
        const auto [p1, p2] = pPoint->remove(bIsFoolPolygon, m_painter);
        m_endingPoint = p1;
        m_startingPoint = p2;
    } else {
        qDebug() << "Unexpected graphic element occurred!";
    }
}
