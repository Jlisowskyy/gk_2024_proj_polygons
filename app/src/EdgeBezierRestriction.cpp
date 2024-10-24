//
// Created by Jlisowskyy on 14/10/24.
//

/* internal includes */
#include "../include/Restrictions/EdgeBezierRestriction.h"
#include "../include/Restrictions/Restrictions.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/BezierPoint.h"
#include "../include/Restrictions/PointContinuousRestriction.h"

/* external includes */
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <cmath>
#include <QGraphicsTextItem>

bool EdgeBezierRestriction::applyRestriction() {
    QPen pen = m_edge->pen();
    QColor color = pen.color();
    color.setAlpha(50);
    pen.setColor(color);
    m_edge->setPen(pen);

    m_edge->setSelected(false);
    m_edge->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, false);
    m_edge->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, false);

    _allocateBezierHelpingPoints();
    _redrawBezierHelpingPoints();
    _drawBezierLine();
    _updateEdgeStorage();

    return false;
}

std::string EdgeBezierRestriction::getIconName() {
    return EdgeRestrictionIconPath("bezier");
}

void EdgeBezierRestriction::onRestrictionDelete() {
    EdgeRestriction::onRestrictionDelete();

    QPen pen = m_edge->pen();
    QColor color = pen.color();
    color.setAlpha(255);
    pen.setColor(color);
    m_edge->setPen(pen);
    m_edge->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, true);
//    m_edge->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsMovable, true);

    _deallocateBezierHelpingPoints();
}

void EdgeBezierRestriction::onReposition() {
    ObjectRestriction::onReposition();

    _redrawBezierHelpingPoints();
    _drawBezierLine();

    if (m_bezierPoint) {
        qDebug() << "PROPAGATED";
        _bezierPointMoved();
    }
}

void EdgeBezierRestriction::_redrawBezierHelpingPoints() {
    Point *pLeft = m_edge->getConnectedElement(LEFT);
    Point *pRight = m_edge->getConnectedElement(RIGHT);

    _updateEdgeStorage();

    m_line1->setLine(pLeft->getPositionOnPainter().x(),
                     pLeft->getPositionOnPainter().y(),
                     m_point1->getPositionOnPainter().x(),
                     m_point1->getPositionOnPainter().y());

    m_line2->setLine(m_point1->getPositionOnPainter().x(),
                     m_point1->getPositionOnPainter().y(),
                     m_point2->getPositionOnPainter().x(),
                     m_point2->getPositionOnPainter().y());

    m_line3->setLine(m_point2->getPositionOnPainter().x(),
                     m_point2->getPositionOnPainter().y(),
                     pRight->getPositionOnPainter().x(),
                     pRight->getPositionOnPainter().y());
}

void EdgeBezierRestriction::_deallocateBezierHelpingPoints() {
    m_line1->scene()->removeItem(m_line1);
    m_line2->scene()->removeItem(m_line2);
    m_line3->scene()->removeItem(m_line3);

    m_point1->scene()->removeItem(m_point1);
    m_point2->scene()->removeItem(m_point2);

    m_bezierLine->scene()->removeItem(m_bezierLine);
}

void EdgeBezierRestriction::_allocateBezierHelpingPoints() {
    QPen linePen(Qt::black);
    linePen.setWidth(BEZIER_HELP_LINE_WIDTH);
    linePen.setStyle(Qt::DashLine);

    m_edge->scene()->addItem(m_line1 = new QGraphicsLineItem());
    m_line1->setPen(linePen);
    m_line1->setZValue(0);
    m_edge->scene()->addItem(m_line2 = new QGraphicsLineItem());
    m_line2->setPen(linePen);
    m_line2->setZValue(0);
    m_edge->scene()->addItem(m_line3 = new QGraphicsLineItem());
    m_line3->setPen(linePen);
    m_line3->setZValue(0);

    Point *pLeft = m_edge->getConnectedElement(LEFT);
    Point *pRight = m_edge->getConnectedElement(RIGHT);
    QPointF posLeft = pLeft->getPositionOnPainter();
    QPointF posRight = pRight->getPositionOnPainter();

    const double midX = (posLeft.x() + posRight.x()) / 2.0;
    const double midY = (posLeft.y() + posRight.y()) / 2.0;

    const double dx = posRight.x() - posLeft.x();
    const double dy = posRight.y() - posLeft.y();

    const double length = std::sqrt(dx * dx + dy * dy);
    const double normX = -(dy / length);
    const double normY = dx / length;

    const double controlPointDistance = length / 4.0;

    const int p1X = static_cast<int>(midX + normX * controlPointDistance);
    const int p1Y = static_cast<int>(midY + normY * controlPointDistance);
    const int p2X = static_cast<int>(midX - normX * controlPointDistance);
    const int p2Y = static_cast<int>(midY - normY * controlPointDistance);

    m_edge->scene()->addItem(m_point1 = new BezierPoint(p1X, p1Y));
    m_edge->scene()->addItem(m_point2 = new BezierPoint(p2X, p2Y));

    m_point1->setEdgeBezierRestriction(this);
    QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(1), m_point1);
    text->setPos(-20, -20);

    m_point2->setEdgeBezierRestriction(this);
    text = new QGraphicsTextItem(QString::number(2), m_point2);
    text->setPos(-20, -20);

    m_edge->scene()->addItem(m_bezierLine = new QGraphicsPathItem());
}


void EdgeBezierRestriction::_drawBezierLine() {
    QPen pen = QPen(BEZIER_HELP_LINE_COLOR);
    pen.setWidth(BEZIER_LINE_LENGTH);

    m_bezierLine->setPen(pen);

    QPainterPath path;
    _fillBezierPath(path);
    m_bezierLine->setPath(path);
}

void EdgeBezierRestriction::_fillBezierPath(QPainterPath &path) {
    Point *pLeft = m_edge->getConnectedElement(LEFT);
    Point *pRight = m_edge->getConnectedElement(RIGHT);

    QPointF startPos = pLeft->getPositionOnPainter();
    QPointF endPos = pRight->getPositionOnPainter();

    QPointF controlPoint1 = m_point1->getPositionOnPainter();
    QPointF controlPoint2 = m_point2->getPositionOnPainter();

    path.moveTo(startPos);

    static constexpr size_t CONTROL_POINTS = 4;

    double x = 0.0;
    double y = 0.0;
    double t = 0.0;
    double step = std::min(0.1, 1.0 /
                                ((m_line2->line().length() + m_line1->line().length() + m_line3->line().length()) / 5));
    double xCords[] = {startPos.x(), controlPoint1.x(), controlPoint2.x(), endPos.x()};
    double yCords[] = {startPos.y(), controlPoint1.y(), controlPoint2.y(), endPos.y()};
    double prevX = startPos.x();
    double prevY = startPos.y();

    while (t <= 1.0) {
        y = x = 0.0;

        const double coefs[]{
                (1 - t) * (1 - t) * (1 - t),
                3 * (1 - t) * (1 - t) * t,
                3 * (1 - t) * t * t,
                t * t * t
        };

        for (size_t j = 0; j < CONTROL_POINTS; j++) {
            x += coefs[j] * xCords[j];
            y += coefs[j] * yCords[j];
        }

        t += step;
        path.lineTo(x, y);
    }
}

bool EdgeBezierRestriction::isRestrictionPreserved() {
    Point *pLeft = m_edge->getConnectedElement(LEFT);
    Point *pRight = m_edge->getConnectedElement(RIGHT);

    ObjectRestriction *restrictionLeft = pLeft->getRestriction();
    if (auto continuousLeft = dynamic_cast<PointContinuousRestriction *>(restrictionLeft); continuousLeft != nullptr) {
        continuousLeft->tryToPreserveRestriction(RIGHT, QPointF(0, 0));
    }

    ObjectRestriction *restrictionRight = pRight->getRestriction();
    if (auto continuousRight = dynamic_cast<PointContinuousRestriction *>(restrictionRight); continuousRight !=
                                                                                             nullptr) {
        continuousRight->tryToPreserveRestriction(LEFT, QPointF(0, 0));
    }

    return true;
}

QPointF
EdgeBezierRestriction::tryToPreserveRestriction([[maybe_unused]] size_t direction, [[maybe_unused]] QPointF dxdy) {
    return {0, 0};
}

BezierPoint *EdgeBezierRestriction::getDirectedBezierPoint(size_t direction) const {
    return direction == LEFT ? m_point2 : m_point1;
}

QGraphicsLineItem *EdgeBezierRestriction::getDirectedBezierEdge(size_t direction) const {
    return direction == LEFT ? m_line3 : m_line1;
}

void EdgeBezierRestriction::_updateEdgeStorage() {
    m_line3->setData(0, m_line3->line());
    m_line1->setData(0, m_line3->line());
}

void EdgeBezierRestriction::_bezierPointMoved() {
    if (m_bezierPoint == m_point1) {
        m_bezierPoint = nullptr;
        _bezierPointMoved(LEFT);
    } else if (m_bezierPoint == m_point2) {
        m_bezierPoint = nullptr;
        _bezierPointMoved(RIGHT);
    } else {
        Q_ASSERT(false);
    }
}

void EdgeBezierRestriction::_bezierPointMoved(size_t direction) {
    Point *point = m_edge->getConnectedElement(direction);
    auto *restriction = dynamic_cast<PointContinuousRestriction *>(point->getRestriction());

    if (restriction != nullptr) {
        restriction->tryToPropagateControlPointChange(direction);
    }
}
