//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Painter.h"
#include "Point.h"

/* external includes */
#include <QGraphicsEllipseItem>
#include <QDebug>

/* internal includes */
#include "ObjectMgr.h"

Painter::Painter(QWidget *parent) : QGraphicsView(parent),
                                    m_scene(new QGraphicsScene(this)) {
    Q_ASSERT(parent != nullptr);
    setScene(m_scene);
    m_scene->setBackgroundBrush(Qt::white);

    /* resize the scene */
    m_scene->setSceneRect(0, 0, width(), height());
    setViewportUpdateMode(FullViewportUpdate);\

    /* disable scrolls visibility */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

Painter::~Painter() {
}

Point *Painter::addPoint(const int x, const int y) const {
    auto *point = new Point(x, y);
    m_scene->addItem(point);
    return point;
}

void Painter::clearContent() const {
    m_scene->clear();
}

void Painter::mousePressEvent(QMouseEvent *event) {
    QGraphicsView::mousePressEvent(event);

    if (m_objectMgr->getIsAddingVertices()) {
        if (const QPoint pos = event->pos(); pos.x() > 0 && pos.y() > 0) {
            m_objectMgr->addPoint(pos.x(), pos.y());
            qDebug() << "Adding point on coordinates: " << pos;
        } else {
            qDebug() << "Point on wrong coordinates: " << pos;
        }
    }
}

void Painter::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    m_scene->setSceneRect(0, 0, width(), height());
}

void Painter::setupPainter(ObjectMgr *objectMgr) {
    Q_ASSERT(objectMgr != nullptr);
    Q_ASSERT(m_objectMgr == nullptr);

    m_objectMgr = objectMgr;
}

Edge *Painter::addEdge(Point *start, Point *end) const {
    auto *edge = new Edge(start, end);
    m_scene->addItem(edge);
    return edge;
}
