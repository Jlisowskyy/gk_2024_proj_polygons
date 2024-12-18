//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_DRAWINGWIDGET_H
#define APP_DRAWINGWIDGET_H

/* external includes */
#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QLabel>
#include <QGraphicsItem>

/* internal includes */
#include "../Constants.h"

/* Forward declaration */
class Polygon;

class Edge;

class Point;

class DrawingWidget : public QGraphicsView {
Q_OBJECT

    // ------------------------------
    // Class constants
    // ------------------------------
public:
    static constexpr int SPACE_WIDTH = 5000;
    static constexpr int SPACE_HEIGHT = 5000;

    // ------------------------------
    // Class creation
    // ------------------------------

    explicit DrawingWidget(QWidget *parent);

    ~DrawingWidget() override;

    // ------------------------------
    // Class interaction
    // ------------------------------

    void setupPainter(Polygon *objectMgr, QLabel *label);

    [[maybe_unused]] Point *addPoint(int x, int y) const;

    [[maybe_unused]] Edge *addEdge(Point *start, Point *end);

    void updateInteractivity();

    [[nodiscard]] bool isMovingSpace() const;

    [[nodiscard]] QGraphicsItem *getSelectedItem() const { return m_selectedItem; }

    void clearSelection();

    [[nodiscard]] LineDrawingAlgorithmType getLineDrawingAlgorithm() const { return m_lineAlgorithmType; }

    [[nodiscard]] Point *getSelectedPoint() const;

    [[nodiscard]] Edge *getSelectedEdge() const;

    // ------------------------------
    // Class slots
    // ------------------------------
public slots:

    void setMovingSpace(bool moving);

    void setUseBresenham(bool useBresenham);

    void setLineDrawingAlgorithm(LineDrawingAlgorithmType type);

    void clearContent() const;

    void removeSelected();

    // ------------------------------
    // Class signals
    // ------------------------------
signals:

    void selectedItemChanged(QGraphicsItem *selectedItem);

    // ------------------------------
    // Protected methods
    // ------------------------------
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void setSelectedItem(QGraphicsItem *item);

    // ------------------------------
    // Private methods
    // ------------------------------

    void _updateSpacePosition() const;

private:
    // ------------------------------
    // Class fields
    // ------------------------------

    QGraphicsItem *m_selectedItem{};
    bool m_isMovingSpace{};

    Polygon *m_polygon{};
    QGraphicsScene *m_scene{};
    QLabel *m_label{};

    LineDrawingAlgorithmType m_lineAlgorithmType = DEFAULT;
};


#endif //APP_DRAWINGWIDGET_H
