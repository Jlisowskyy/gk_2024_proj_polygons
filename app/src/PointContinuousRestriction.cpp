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

    if (edgeBezierLeft && edgeBezierRight) {
        _processDoubleBezierInit();
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
PointContinuousRestriction::tryToPreserveRestriction(const size_t direction, [[maybe_unused]] const QPointF dxdy) {
    return _processDirectionBezier(direction);
}

QPointF
PointContinuousRestriction::_processDirectionBezier(const size_t direction) {
    const size_t reverseDirection = swapDirection(direction);
    auto *bezier = dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(direction)->getRestriction());
    Q_ASSERT(bezier != nullptr);

    if (bezier->getBlockPropagation()) {
        return {0, 0};
    }

    if (m_point->getConnectedElement(reverseDirection) == nullptr) {
        return {0, 0};
    }

    if (dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(
            reverseDirection)->getRestriction())) {
        return {0, 0};
    }

    BezierPoint *bezierPoint = bezier->getDirectedBezierPoint(direction);
    Q_ASSERT(bezierPoint != nullptr);

    const QPointF prevPoint = m_point->getConnectedElement(reverseDirection)->getConnectedElement(
            reverseDirection)->getPositionOnPainter();

    QLineF line(prevPoint, m_point->getPositionOnPainter());
    if (m_coef != 0) {
        line.setLength(m_coef * line.length());
    } else {
        QLineF line1(bezierPoint->getPrevPos(), m_point->getPositionOnPainter());
        line.setLength(line1.length() + line.length());
    }

    BlockBezierPropagation = true;
    bezierPoint->setPositionOnPainter(line.p2());
    BlockBezierPropagation = false;

    return {0, 0};
}

bool PointContinuousRestriction::tryToPropagateControlPointChange(const size_t direction) {
    Point *nextPoint = m_point->getConnectedPoint(direction);

    if (nextPoint == nullptr) {
        return true;
    }

    if (dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(direction)->getRestriction())) {
        _processDoubleBezierControlPointMove(direction);
        return true;
    }

    Edge *edge = m_point->getConnectedElement(direction);
    const size_t reverseDirection = swapDirection(direction);

    auto *bezier = dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(
            reverseDirection)->getRestriction());
    Q_ASSERT(bezier != nullptr);

    BezierPoint *bezierPoint = bezier->getDirectedBezierPoint(reverseDirection);
    Q_ASSERT(bezierPoint != nullptr);

    const QLineF prevLine(bezierPoint->getPrevPos(), m_point->getPositionOnPainter());
    QLineF curLine(bezierPoint->getPositionOnPainter(), m_point->getPositionOnPainter());

    qreal point1Dist;
    qreal point2Dist;
    if (m_coef == 0) {
        point1Dist = curLine.length();
        point2Dist = edge->getLength();
    } else {
//        const qreal bCoef = m_coef - 1.0;
//        const qreal reversedCoef = 1.0 / (bCoef);
//        expectedLength = (1.0 + reversedCoef) * prevLen;

        point1Dist = prevLine.length();
        point2Dist = edge->getLength();
    }


    QLineF moveLine1(bezierPoint->getPositionOnPainter(), m_point->getPositionOnPainter());
    moveLine1.setLength(point1Dist);

    QLineF moveLine2(bezierPoint->getPositionOnPainter(), m_point->getPositionOnPainter());
    moveLine2.setLength(point2Dist + point1Dist);

    const QPointF move1dxdy = moveLine1.p2() - m_point->getPositionOnPainter();
    const QPointF move2dxdy = moveLine2.p2() - nextPoint->getPositionOnPainter();

    bezier->setBlockPropagation(true);

    bool wasMoved = m_point->tryToMovePoint(move1dxdy, [&]() {
        return nextPoint->tryToMovePoint(move2dxdy, [&]() {
            return nextPoint->tryToPreserveRestrictions(move2dxdy, direction, nullptr, true, nullptr) &&
                   nextPoint->areRestrictionsPreserved() && m_point->areRestrictionsPreserved();
        });
    });

    if (!wasMoved) {
        const QPointF moveDxdy = bezierPoint->getPositionOnPainter() - bezierPoint->getPrevPos();
        m_point->moveWholePolygon(moveDxdy);
        BlockPropagation = true;
        m_point->moveBy(moveDxdy.x(), moveDxdy.y());
        m_point->updateEdgePositions();
        BlockPropagation = false;
        bezier->getDirectedBezierPoint(direction)->moveBy(moveDxdy.x(), moveDxdy.y());
    } else {
        nextPoint->tryToPreserveRestrictions(move2dxdy, direction, nullptr, false, nullptr);
        m_point->updateEdgePositions();
    }
    bezier->setBlockPropagation(false);

    return false;
}

void PointContinuousRestriction::_processDoubleBezierInit() {
    _processDoubleBezierControlPointMove(LEFT);
}

void PointContinuousRestriction::_processDoubleBezierControlPointMove(const size_t direction) {
    auto *bezierDir = dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(direction)->getRestriction());
    auto *bezierRev = dynamic_cast<EdgeBezierRestriction *>(m_point->getConnectedElement(
            swapDirection(direction))->getRestriction());

    Q_ASSERT(bezierDir != nullptr);
    Q_ASSERT(bezierRev != nullptr);

    BezierPoint *bezierPointDir = bezierDir->getDirectedBezierPoint(direction);
    BezierPoint *bezierPointRev = bezierRev->getDirectedBezierPoint(swapDirection(direction));

    QLineF line(bezierPointRev->getPositionOnPainter(), m_point->getPositionOnPainter());
    if (m_coef == 0) {
        QLineF line1(m_point->getPositionOnPainter(), bezierPointDir->getPositionOnPainter());

        line.setLength(line.length() + line1.length());
    } else {
        line.setLength(2 * line.length());
    }

    bezierPointDir->setPositionOnPainter(line.p2());
}
