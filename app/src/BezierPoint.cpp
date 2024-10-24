//
// Created by Jlisowskyy on 15/10/24.
//

/* internal includes */
#include "../include/GraphicObjects/BezierPoint.h"
#include "../include/Constants.h"
#include "../include/Restrictions/EdgeBezierRestriction.h"

/* external includes */
#include <QPen>
#include <QBrush>

BezierPoint::BezierPoint(const int x, const int y) :
        QGraphicsEllipseItem(
                0,
                0,
                BEZIER_CONTROL_POINT_RADIUS * 2,
                BEZIER_CONTROL_POINT_RADIUS * 2), m_edgeBezierRestriction(nullptr) {
    setFlags(flags() | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsScenePositionChanges);
    setPen(QPen(DEFAULT_COLOR));
    setBrush(QBrush(DEFAULT_COLOR));
    setPos(QPointF(x - DEFAULT_POINT_RADIUS, y - DEFAULT_POINT_RADIUS));

    /* Points should be displayed above edges */
    setZValue(2);
}

QPointF BezierPoint::getPositionOnPainter() const {
    return scenePos() + QPointF(BEZIER_CONTROL_POINT_RADIUS, BEZIER_CONTROL_POINT_RADIUS);
}

QVariant BezierPoint::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case QGraphicsItem::GraphicsItemChange::ItemPositionHasChanged:
            _onPositionChange();
            return value;
        case QGraphicsItem::GraphicsItemChange::ItemPositionChange:
            m_prevPos = getPositionOnPainter();
        default:
            return QGraphicsEllipseItem::itemChange(change, value);
    }
}

void BezierPoint::_onPositionChange() {
    if (!m_edgeBezierRestriction) {
        return;
    }

    if (!BlockBezierPropagation) {
        m_edgeBezierRestriction->setBezierPointMoving(this);
    }
    m_edgeBezierRestriction->onReposition();
}
