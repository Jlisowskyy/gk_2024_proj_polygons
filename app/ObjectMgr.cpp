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

    addPoint(3 * 50, 3 * 50);
    addPoint(3 * 100, 3 * 50);
    addPoint(3 * 100, 3 * 100);
}

void ObjectMgr::clearItems() {
    m_edges.clear();
    m_points.clear();
    m_painter->clearContent();
}

void ObjectMgr::addPoint(int x, int y) {
    auto *point = m_painter->addPoint(x, y);
    m_points.push_back(point);

    if (m_points.size() > 1) {
        auto *prevPoint = m_points[m_points.size() - 2];
        auto *edge = m_painter->addEdge(prevPoint, point);
        m_edges.push_back(edge);
    }
}
