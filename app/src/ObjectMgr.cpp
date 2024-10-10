//
// Created by Jlisowskyy on 09/10/24.
//

#include "ObjectMgr.h"

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
    m_edges.clear();
    m_points.clear();
}

bool ObjectMgr::getIsAddingVertices() const {
    return m_isAddingVertices;
}

void ObjectMgr::setIsAddingVertices(const bool value) {
    m_isAddingVertices = value;
    m_painter->updateInteractivity();
}

bool ObjectMgr::isFullPolygon() const {
    return m_points.size() >= 2 &&
           m_points[0]->getPositionOnPainter() == m_points[m_points.size() - 1]->getPositionOnPainter();
}

Point *ObjectMgr::findPointSpot(const int x, const int y) const {
    if (m_points.size() < 3) {
        return m_painter->addPoint(x, y);
    }

    const int xDist = x - m_points[0]->getPositionOnPainter().toPoint().x();
    const int yDist = y - m_points[0]->getPositionOnPainter().toPoint().y();
    const bool isInsideHitBox = xDist * xDist + yDist * yDist <= FINAL_POINT_HIT_BOX_SIZE * FINAL_POINT_HIT_BOX_SIZE;
    const int xAdjusted = isInsideHitBox ? m_points[0]->getPositionOnPainter().toPoint().x() : x;
    const int yAdjusted = isInsideHitBox ? m_points[0]->getPositionOnPainter().toPoint().y() : y;

    return m_painter->addPoint(xAdjusted, yAdjusted);
}

void ObjectMgr::addPoint(const int x, const int y) {
    if (!getIsAddingVertices() || isFullPolygon()) {
        return;
    }

    auto *point = findPointSpot(x, y);
    m_points.push_back(point);

    if (m_points.size() > 1) {
        auto *prevPoint = m_points[m_points.size() - 2];
        auto *edge = m_painter->addEdge(prevPoint, point);
        m_edges.push_back(edge);

        prevPoint->setConnectedEdge(RIGHT, edge);
        point->setConnectedEdge(LEFT, edge);

        if (isFullPolygon()) {
            Point *firstPoint = m_points[0];
            Point *lastPoint = m_points[m_points.size() - 1];

            lastPoint->setConnectedEdge(RIGHT, edge);
            firstPoint->setConnectedEdge(LEFT, edge);
        }
    }
}
