//
// Created by Jlisowskyy on 08/10/24.
//

/* internal includes */
#include "../include/GraphicObjects/DrawingWidget.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/ManagingObjects/Polygon.h"
#include "../include/GraphicObjects/Edge.h"

/* external includes */
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <format>
#include <QShortcut>

DrawingWidget::DrawingWidget(QWidget *parent) : QGraphicsView(parent),
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

    centerOn(SPACE_WIDTH / 2, SPACE_HEIGHT / 2);
}

DrawingWidget::~DrawingWidget() {
    clearContent();
}

Point *DrawingWidget::addPoint(const int x, const int y) const {
    auto *point = new Point(x, y, m_polygon);
    m_scene->addItem(point);
    return point;
}

void DrawingWidget::clearContent() const {
    m_scene->clear();
}

void DrawingWidget::setMovingSpace(const bool moving) {
    m_isMovingSpace = moving;

    setDragMode(moving ? ScrollHandDrag : NoDrag);
    updateInteractivity();
}

bool DrawingWidget::isMovingSpace() const {
    return m_isMovingSpace;
}

void DrawingWidget::updateInteractivity() {
    m_scene->clearSelection();
    setInteractive(!m_isMovingSpace && !m_polygon->getIsAddingVertices());
}

void DrawingWidget::mousePressEvent(QMouseEvent *event) {
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

    QPoint scenePos = mapToScene(event->pos()).toPoint();

    if (scenePos.x() > 0 && scenePos.y() > 0) {
        m_polygon->addPoint(scenePos.x(), scenePos.y());
        qDebug() << "Adding point on coordinates: " << scenePos;
    } else {
        qDebug() << "Point on wrong coordinates: " << scenePos;
    }
}

void DrawingWidget::mouseMoveEvent(QMouseEvent *event) {
    QGraphicsView::mouseMoveEvent(event);
    _updateSpacePosition();
}

void DrawingWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    _updateSpacePosition();
}

void DrawingWidget::_updateSpacePosition() const {
    const QPointF topLeft = mapToScene(viewport()->rect().topLeft());
    const QPointF bottomRight = mapToScene(viewport()->rect().bottomRight());

    const std::string text = std::format("Space coordinates: Top-left: ({}, {}), Bottom-right: ({}, {})",
                                         topLeft.x(), topLeft.y(), bottomRight.x(), bottomRight.y());

    m_label->setText(QString::fromStdString(text));
}

void DrawingWidget::setupPainter(Polygon *objectMgr, QLabel *label) {
    Q_ASSERT(objectMgr != nullptr);
    Q_ASSERT(m_polygon == nullptr);
    m_polygon = objectMgr;

    Q_ASSERT(label != nullptr);
    Q_ASSERT(m_label == nullptr);
    m_label = label;

    _updateSpacePosition();
}

Edge *DrawingWidget::addEdge(Point *start, Point *end) {
    auto *edge = new Edge(start, end, this, m_polygon);
    m_scene->addItem(edge);
    return edge;
}

void DrawingWidget::setSelectedItem(QGraphicsItem *item) {
    if (m_selectedItem == item) {
        return;
    }

    m_selectedItem = item;
    emit selectedItemChanged(item);
}

void DrawingWidget::clearSelection() {
    scene()->clearSelection();
}

void DrawingWidget::removeSelected() {
    m_polygon->removeSelection();
}

void DrawingWidget::setLineDrawingAlgorithm(LineDrawingAlgorithmType type) {
    m_lineAlgorithmType = type;

    m_scene->update();
}

void DrawingWidget::setUseBresenham(bool useBresenham) {
    setLineDrawingAlgorithm(useBresenham ? BRESENHAM : DEFAULT);
}

Point *DrawingWidget::getSelectedPoint() const {
    return dynamic_cast<Point *>(getSelectedItem());
}

Edge *DrawingWidget::getSelectedEdge() const {
    return dynamic_cast<Edge *>(getSelectedItem());
}
