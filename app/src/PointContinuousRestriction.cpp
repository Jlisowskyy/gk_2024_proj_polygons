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

bool PointContinuousRestriction::applyRestriction() {
    return false;
}

std::string PointContinuousRestriction::getIconName() {
    return PointIconRestrictionPath("continuous");
}

bool PointContinuousRestriction::isRestrictionPreserved() {
    return true;
}

QPointF
PointContinuousRestriction::tryToPreserveRestriction(size_t direction, [[maybe_unused]] QPointF dxdy) {
    Edge *edge = m_point->getConnectedElement(direction);
    if (edge == nullptr) {
        return {0, 0};
    }

    ObjectRestriction *restriction = edge->getRestriction();

    if (auto *bezier = dynamic_cast<EdgeBezierRestriction *>(restriction)) {
        return _processDirectionBezier(direction, dxdy, bezier);
    }

    qDebug() << "NOT IMPLEMENTED";
    return {0, 0};
}

QPointF
PointContinuousRestriction::_processDirectionBezier(size_t direction, QPointF dxdy, EdgeBezierRestriction *bezier) {
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
    line.setLength(4 * line.length() / 3);

    bezierPoint->setPos(line.p2());
    return {0, 0};
}

