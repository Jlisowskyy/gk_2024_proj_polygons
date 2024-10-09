//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Painter.h"
#include "Point.h"

/* external includes */
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <format>

/* internal includes */
#include "ObjectMgr.h"

Painter::Painter(QWidget *parent) : QGraphicsView(parent),
                                    m_scene(new QGraphicsScene(this)) {
    Q_ASSERT(parent != nullptr);
    setScene(m_scene);
    m_scene->setBackgroundBrush(Qt::white);

    /* resize the scene */
    m_scene->setSceneRect(0,
                          0,
                          SPACE_WIDTH,
                          SPACE_HEIGHT);

    /* disable scrolls visibility */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* Additional space options */
    setViewportUpdateMode(FullViewportUpdate);
    setRenderHint(QPainter::Antialiasing, true);
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

void Painter::setMovingSpace(const bool moving) {
    m_isMovingSpace = moving;

    setDragMode(moving ? ScrollHandDrag : NoDrag);
    updateInteractivity();
}

bool Painter::isMovingSpace() const {
    return m_isMovingSpace;
}

void Painter::updateInteractivity() {
    m_scene->clearSelection();
    setInteractive(!m_isMovingSpace && !m_objectMgr->getIsAddingVertices());
}

void Painter::mousePressEvent(QMouseEvent *event) {
    if (m_scene) {

        /* Ensure only single item can be selected */
        m_scene->clearSelection();
    }

    QGraphicsView::mousePressEvent(event);

    if (event->button() != Qt::LeftButton) {
        return;
    }

    if (isMovingSpace()) {
        return;
    }

    if (const QPoint pos = event->pos(); pos.x() > 0 && pos.y() > 0) {
        m_objectMgr->addPoint(pos.x(), pos.y());
        qDebug() << "Adding point on coordinates: " << pos;
    } else {
        qDebug() << "Point on wrong coordinates: " << pos;
    }
}

void Painter::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
    updateSpacePosition();
}

void Painter::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    updateSpacePosition();
}

void Painter::updateSpacePosition() const {
    const QPointF topLeft = mapToScene(viewport()->rect().topLeft());
    const QPointF bottomRight = mapToScene(viewport()->rect().bottomRight());

    const std::string text = std::format("Space coordinates: Top-left: ({}, {}), Bottom-right: ({}, {})",
                                         topLeft.x(), topLeft.y(), bottomRight.x(), bottomRight.y());

    m_label->setText(QString::fromStdString(text));
}

void Painter::setupPainter(ObjectMgr *objectMgr, QLabel *label) {
    Q_ASSERT(objectMgr != nullptr);
    Q_ASSERT(m_objectMgr == nullptr);
    m_objectMgr = objectMgr;

    Q_ASSERT(label != nullptr);
    Q_ASSERT(m_label == nullptr);
    m_label = label;

    updateSpacePosition();
}

Edge *Painter::addEdge(Point *start, Point *end) const {
    auto *edge = new Edge(start, end);
    m_scene->addItem(edge);
    return edge;
}
