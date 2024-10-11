//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "Painter.h"
#include "Point.h"
#include "ObjectMgr.h"

/* external includes */
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <format>
#include <QShortcut>

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

    new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(removeSelected()));
}

Painter::~Painter() {
    clearContent();
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

    setSelectedItem(m_scene->selectedItems().empty() ? nullptr : m_scene->selectedItems()[0]);

    if (event->button() != Qt::LeftButton) {
        return;
    }

    if (isMovingSpace()) {
        return;
    }

    // Convert the mouse position from view coordinates to scene coordinates
    QPoint scenePos = mapToScene(event->pos()).toPoint();

    if (scenePos.x() > 0 && scenePos.y() > 0) {
        m_objectMgr->addPoint(scenePos.x(), scenePos.y());
        qDebug() << "Adding point on coordinates: " << scenePos;
    } else {
        qDebug() << "Point on wrong coordinates: " << scenePos;
    }
}

void Painter::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
    _updateSpacePosition();
}

void Painter::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    _updateSpacePosition();
}

void Painter::_updateSpacePosition() const {
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

    _updateSpacePosition();
}

Edge *Painter::addEdge(Point *start, Point *end) const {
    auto *edge = new Edge(start, end);
    m_scene->addItem(edge);
    return edge;
}

void Painter::setSelectedItem(QGraphicsItem *item) {
    if (m_selectedItem == item) {
        return;
    }

    m_selectedItem = item;
    emit selectedItemChanged(item);
}

void Painter::clearSelection() {
    scene()->clearSelection();
}

void Painter::removeSelected() {
    m_objectMgr->removeSelection();
}
