//
// Created by Jlisowskyy on 14/10/24.
//

/* internal includes */
#include "../include/Restrictions/EdgeBezierRestriction.h"
#include "../include/Restrictions/Restrictions.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/GraphicObjects/BezierPoint.h"

/* external includes */
#include <QPen>
#include <QColor>
#include <QGraphicsItem>
#include <QGraphicsScene>

bool EdgeBezierRestriction::applyRestriction() {
    QPen pen = m_edge->pen();
    QColor color = pen.color();
    color.setAlpha(50);
    pen.setColor(color);
    m_edge->setPen(pen);

    m_edge->setSelected(false);
    m_edge->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, false);

    _allocateBezierHelpingPoints();
    _redrawBezierHelpingPoints();
    _drawBezierLine();

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

    _deallocateBezierHelpingPoints();
}

void EdgeBezierRestriction::onReposition() {
    ObjectRestriction::onReposition();

    _redrawBezierHelpingPoints();
    _drawBezierLine();
}

void EdgeBezierRestriction::_redrawBezierHelpingPoints() {
    Point *pLeft = m_edge->getConnectedElement(LEFT);
    Point *pRight = m_edge->getConnectedElement(RIGHT);

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
    m_edge->scene()->addItem(m_line2 = new QGraphicsLineItem());
    m_line2->setPen(linePen);
    m_edge->scene()->addItem(m_line3 = new QGraphicsLineItem());
    m_line3->setPen(linePen);

    Point *pLeft = m_edge->getConnectedElement(LEFT);
    Point *pRight = m_edge->getConnectedElement(RIGHT);
    QPointF posLeft = pLeft->getPositionOnPainter();
    QPointF posRight = pRight->getPositionOnPainter();

    const int midX = static_cast<int>((posLeft.x() + posRight.x()) / 2.0);
    const int midY = static_cast<int>((posLeft.y() + posRight.y()) / 2.0);
    const int xLen = static_cast<int>(abs(posLeft.x() - posRight.x()) / 4.0);
    const int yLen = static_cast<int>(abs(posLeft.y() - posRight.y()) / 4.0);

    const int p1X = midX - xLen;
    const int p1Y = midY + yLen;
    const int p2X = midX + xLen;
    const int p2Y = midY - yLen;

    m_edge->scene()->addItem(m_point1 = new BezierPoint(p1X, p1Y));
    m_edge->scene()->addItem(m_point2 = new BezierPoint(p2X, p2Y));

    m_point1->setEdgeBezierRestriction(this);
    m_point2->setEdgeBezierRestriction(this);

    m_edge->scene()->addItem(m_bezierLine = new QGraphicsPathItem());
}

void EdgeBezierRestriction::_drawBezierLine() {
    QPainterPath path;

    Point *pLeft = m_edge->getConnectedElement(LEFT);
    Point *pRight = m_edge->getConnectedElement(RIGHT);

    QPointF startPos = pLeft->getPositionOnPainter();
    QPointF endPos = pRight->getPositionOnPainter();

    QPointF controlPoint1 = m_point1->getPositionOnPainter();
    QPointF controlPoint2 = m_point2->getPositionOnPainter();

    path.moveTo(startPos);

    path.cubicTo(controlPoint1, controlPoint2, endPos);

    QPen pen = QPen(BEZIER_HELP_LINE_COLOR);
    pen.setWidth(BEZIER_LINE_LENGTH);

    m_bezierLine->setPen(pen);
    m_bezierLine->setPath(path);
}
