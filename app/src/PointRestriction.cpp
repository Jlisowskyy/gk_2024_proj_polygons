//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/PointRestriction.h"
#include "../include/GraphicObjects/Point.h"

void PointRestriction::onRestrictionDelete() {
    m_point->cleanRestriction();
}

QPoint PointRestriction::getIconPosition() {
    return (m_point->getPositionOnPainter() + QPointF(-24, -60)).toPoint();
}
