//
// Created by Jlisowskyy on 09/10/24.
//

/* internal includes */
#include "../include/ManagingObjects/Polygon.h"
#include "../include/Interfaces/IPolygonObject.h"
#include "../include/Restrictions/Restrictions.h"
#include "../include/Restrictions/EdgeRestriction.h"
#include "../include/Restrictions/PointRestriction.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/DrawingWidget.h"
#include "../include/Restrictions/EdgeConstLengthRestriction.h"

/* external includes */

Polygon::Polygon(QObject *parent) : QObject(parent) {
    Q_ASSERT(parent != nullptr);
}

void Polygon::setupMgr(DrawingWidget *painter) {
    Q_ASSERT(painter != nullptr);
    Q_ASSERT(m_drawingWidget == nullptr);
    m_drawingWidget = painter;

    setIsAddingVertices(true);
    const auto p1 = m_drawingWidget->mapToScene(150, 150);
    addPoint(p1.x(), p1.y());
    const auto p2 = m_drawingWidget->mapToScene(330, 120);
    addPoint(p2.x(), p2.y());
    const auto p3 = m_drawingWidget->mapToScene(300, 300);
    addPoint(p3.x(), p3.y());
    setIsAddingVertices(false);

    auto edge1 = m_startingPoint->getConnectedElement(RIGHT);
    edge1->applyRestriction(EdgeRestrictions["bezier"](edge1), m_drawingWidget);
    auto edge2 = m_endingPoint->getConnectedElement(LEFT);
    edge2->applyRestriction(new EdgeConstLengthRestriction(edge2, edge2->line().length()), m_drawingWidget);
}

void Polygon::clearItems() {
    m_drawingWidget->clearContent();

    m_startingPoint = m_endingPoint = nullptr;
    m_pointCount = 0;
}

bool Polygon::getIsAddingVertices() const {
    return m_isAddingVertices;
}

void Polygon::setIsAddingVertices(const bool value) {
    m_isAddingVertices = value;
    m_drawingWidget->updateInteractivity();
}

bool Polygon::isFullPolygon() const {
    return m_startingPoint != nullptr && m_endingPoint != nullptr &&
           m_endingPoint->getConnectedElement(RIGHT) != nullptr;
}

Point *Polygon::_findPointSpot(const int x, const int y) const {
    if (m_endingPoint == nullptr || m_startingPoint->getConnectedElement(RIGHT) == nullptr
        || m_endingPoint->getConnectedElement(LEFT)->getConnectedElement(LEFT) == m_startingPoint) {
        return m_drawingWidget->addPoint(x, y);
    }

    const int xDist = x - m_startingPoint->getPositionOnPainter().toPoint().x();
    const int yDist = y - m_startingPoint->getPositionOnPainter().toPoint().y();
    const bool isInsideHitBox = xDist * xDist + yDist * yDist <= FINAL_POINT_HIT_BOX_SIZE * FINAL_POINT_HIT_BOX_SIZE;

    return isInsideHitBox ? nullptr : m_drawingWidget->addPoint(x, y);
}

void Polygon::addPoint(const int x, const int y) {
    if (!getIsAddingVertices() || isFullPolygon()) {
        return;
    }

    auto *point = _findPointSpot(x, y);

    if (point == nullptr) {
        auto *edge = m_drawingWidget->addEdge(m_endingPoint, m_startingPoint);

        m_endingPoint->setConnectedElement(RIGHT, edge);
        m_startingPoint->setConnectedElement(LEFT, edge);

        qDebug() << m_startingPoint->countPoints();
    } else {
        if (m_startingPoint == nullptr) {
            m_startingPoint = m_endingPoint = point;
        } else {
            auto *edge = m_drawingWidget->addEdge(m_endingPoint, point);

            m_endingPoint->setConnectedElement(RIGHT, edge);
            point->setConnectedElement(LEFT, edge);

            m_endingPoint = point;
        }
    }
}

void Polygon::removeSelection() {
    QGraphicsItem *selectedItem = m_drawingWidget->getSelectedItem();

    if (selectedItem == nullptr) {
        return;
    }

    const bool bIsFoolPolygon = isFullPolygon();
    m_drawingWidget->clearSelection();

    auto *pObject = dynamic_cast<IPolygonObject *>(selectedItem);
    Q_ASSERT(pObject != nullptr);

    const auto [p1, p2] = pObject->remove(bIsFoolPolygon, m_drawingWidget);
    m_startingPoint = p1;
    m_endingPoint = p2;
}

void Polygon::cutEdge() {
    Edge *edge = m_drawingWidget->getSelectedEdge();
    Q_ASSERT(edge != nullptr);

    edge->cutEdge(m_drawingWidget);
}

void Polygon::setEdgeRestriction(const std::string &restrictionName) {
    Edge *edge = m_drawingWidget->getSelectedEdge();
    Q_ASSERT(edge != nullptr);
    Q_ASSERT(EdgeRestrictions.find(restrictionName) != EdgeRestrictions.end());

    edge->applyRestriction(EdgeRestrictions[restrictionName](edge), m_drawingWidget);
}

void Polygon::setPointRestriction(const std::string &restrictionName) {
    Point *point = m_drawingWidget->getSelectedPoint();
    Q_ASSERT(point != nullptr);
    Q_ASSERT(PointRestrictions.find(restrictionName) != PointRestrictions.end());

    point->applyRestriction(PointRestrictions[restrictionName](point), m_drawingWidget);
}

int Polygon::getAndIncrementPointCount() {
    return m_pointCount++;
}

void Polygon::moveVertex(const int vertexIdx, const QPointF dxdy) {
    if (m_startingPoint == nullptr) {
        return;
    }

    m_startingPoint->iteratePoints([&](Point *point) {
        if (point != nullptr && point->getId() == vertexIdx) {
            point->moveBy(dxdy.x(), dxdy.y());
        }
    });
}

DrawingWidget *Polygon::getDrawingWidget() const {
    return m_drawingWidget;
}
