//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "../include/GraphicObjects/Point.h"
#include "../include/Constants.h"
#include "../include/ManagingObjects/Polygon.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/DrawingWidget.h"
#include "../include/Interfaces/IPointPolygonObject.h"
#include "../include/Restrictions/ObjectRestriction.h"

/* external includes */
#include <QPen>
#include <QBrush>
#include <QDebug>
#include <QVariant>

Point::Point(const int x, const int y) : QGraphicsEllipseItem(0,
                                                              0,
                                                              DEFAULT_POINT_RADIUS * 2,
                                                              DEFAULT_POINT_RADIUS * 2),
                                         IConnectableElement<Edge>(reinterpret_cast<void *>(this)),
                                         IPointPolygonObject(this) {
    setFlags(flags() | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
             QGraphicsItem::ItemSendsScenePositionChanges);
    setPen(QPen(DEFAULT_COLOR));
    setBrush(QBrush(DEFAULT_COLOR));
    setPos(QPointF(x - DEFAULT_POINT_RADIUS, y - DEFAULT_POINT_RADIUS));

    /* Points should be displayed above edges */
    setZValue(1);

}

QVariant Point::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) {
    switch (change) {
        case GraphicsItemChange::ItemPositionChange:
            return _onPositionChange(value);
        case GraphicsItemChange::ItemSelectedHasChanged:
            return _onSelectionChange(value);
        case GraphicsItemChange::ItemPositionHasChanged:
            return _onPositionChanged(value);
        case GraphicsItemChange::ItemSceneHasChanged:
            if (scene() == nullptr) {
                onRemoved();
            }
            return value;
        default:
            return QGraphicsEllipseItem::itemChange(change, value);
    }
}

QVariant Point::_onPositionChange(const QVariant &value) {
    return value;
}

QVariant Point::_onSelectionChange(const QVariant &value) {
    setPen(QPen(isSelected() ? SELECTED_COLOR : DEFAULT_COLOR));
    setBrush(QBrush(isSelected() ? SELECTED_COLOR : DEFAULT_COLOR));

    const auto prevRadius = rect().width() / 2;
    const auto radius = getRadius();
    setRect(QRectF(
            0,
            0,
            radius * 2,
            radius * 2
    ));

    const double offset = prevRadius - radius;
    setPos(scenePos() + QPointF(offset, offset));

    return value;
}

QPointF Point::getPositionOnPainter() const {
    const auto radius = getRadius();
    const auto pos = scenePos() + QPointF(radius, radius);

    return pos;
}

QVariant Point::_onPositionChanged(const QVariant &value) {
    for (auto &m_edge: m_connectedElements) {
        if (m_edge) {
            m_edge->repositionByPoints();
        }
    }

    if (m_restriction) {
        m_restriction->onReposition();
    }

    return value;
}

double Point::getRadius() const {
    return static_cast<double>(isSelected() ? SELECTED_POINT_RADIUS : DEFAULT_POINT_RADIUS);
}
