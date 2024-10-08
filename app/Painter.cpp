//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Painter.h"
#include "Point.h"

/* external includes */
#include <QGraphicsEllipseItem>

Painter::Painter(QWidget *parent) :
        QGraphicsView(parent),
        m_scene(new QGraphicsScene(this)) {
    Q_ASSERT(parent != nullptr);
    setScene(m_scene);
    m_scene->setBackgroundBrush(Qt::white);
}

Painter::~Painter() {

}

Point *Painter::addPoint(int x, int y) {
    auto *point = new Point(x, y);
    m_scene->addItem(point);
    return point;
}

void Painter::clearContent() {
    m_scene->clear();
}

void Painter::setupPainter(ObjectMgr *objectMgr) {
    Q_ASSERT(objectMgr != nullptr);
    Q_ASSERT(m_objectMgr == nullptr);

    m_objectMgr = objectMgr;
}

Edge *Painter::addEdge(Point *start, Point *end) {
    auto *edge = new Edge(start, end);
    m_scene->addItem(edge);
    return edge;
}

