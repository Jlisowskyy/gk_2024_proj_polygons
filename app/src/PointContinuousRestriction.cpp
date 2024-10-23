//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/Restrictions.h"
#include "../include/Restrictions/PointContinuousRestriction.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/Restrictions/EdgeBezierRestriction.h"
#include "../include/GraphicObjects/BezierPoint.h"

PointContinuousRestriction::PointContinuousRestriction(Point *point, const qreal coef) : PointRestriction(point),
                                                                                         m_coef(coef) {
}

bool PointContinuousRestriction::applyRestriction() {
    Edge *edgeLeft = m_point->getConnectedElement(LEFT);
    Edge *edgeRight = m_point->getConnectedElement(RIGHT);

    auto *edgeBezierLeft = edgeLeft ? dynamic_cast<EdgeBezierRestriction *>(edgeLeft->getRestriction()) : nullptr;
    auto *edgeBezierRight = edgeRight ? dynamic_cast<EdgeBezierRestriction *>(edgeRight->getRestriction()) : nullptr;

    if (edgeBezierLeft && edgeBezierRight && m_coef != 0) {
        return true;
    }

    if (edgeBezierLeft) {
        _processDirectionBezier(LEFT);
    }

    if (edgeBezierRight) {
        _processDirectionBezier(RIGHT);
    }

    return false;
}

bool PointContinuousRestriction::isRestrictionPreserved() {
    return true;
}

QPointF
PointContinuousRestriction::tryToPreserveRestriction(size_t direction, [[maybe_unused]] QPointF dxdy) {
    _processDirectionBezier(direction);
    return {0, 0};
}

QPointF
PointContinuousRestriction::_processDirectionBezier(size_t direction) {
    auto *bezier = dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(direction)->getRestriction());
    Q_ASSERT(bezier != nullptr);

    const size_t reverseDirection = swapDirection(direction);
    BezierPoint *bezierPoint = bezier->getDirectedBezierPoint(direction);
    Q_ASSERT(bezierPoint != nullptr);

    QPointF prevPoint;
    if (auto *prevBezier = dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(
            reverseDirection)->getRestriction())) {
        BezierPoint *prevBezierPoint = prevBezier->getDirectedBezierPoint(reverseDirection);
        Q_ASSERT(prevBezierPoint != nullptr);
        prevPoint = prevBezierPoint->getPositionOnPainter();
    } else {
        prevPoint = m_point->getConnectedElement(reverseDirection)->getConnectedElement(
                reverseDirection)->getPositionOnPainter();
    }

    QLineF line(prevPoint, m_point->getPositionOnPainter());
    if (m_coef != 0) {
        line.setLength(m_coef * line.length());
    } else {
        QGraphicsLineItem *bezierEdge = bezier->getDirectedBezierEdge(direction);
        const qreal bezierLength = bezierEdge->line().length();
        const qreal edgeLength = line.length();
        const qreal totalLength = bezierLength + edgeLength;

        line.setLength(totalLength);
    }

    bezierPoint->setPos(line.p2());
    return {0, 0};
}

bool PointContinuousRestriction::tryToPropagateControlPointChange(size_t direction) {
    Edge *edge = m_point->getConnectedElement(direction);
    const size_t reverseDirection = swapDirection(direction);

    auto *bezier = dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(
            reverseDirection)->getRestriction());
    Q_ASSERT(bezier != nullptr);

    BezierPoint *bezierPoint = bezier->getDirectedBezierPoint(direction);
    Q_ASSERT(bezierPoint != nullptr);

    QLineF line(bezierPoint->getPositionOnPainter(), m_point->getPositionOnPainter());
    qreal expectedLength;

    if (m_coef == 0) {
        expectedLength = edge->line().length();
    } else {
        qreal reversedCoef = 1.0 / (1.0 - m_coef);

        expectedLength = reversedCoef * line.length();
    }


    return false;
}
