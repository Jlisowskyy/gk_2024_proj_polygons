//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_PAINTER_H
#define APP_PAINTER_H

/* external includes */
#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QLabel>
#include <QGraphicsItem>

/* internal includes */
#include "Point.h"
#include "Edge.h"

/* Forward declaration */
class ObjectMgr;

class Painter : public QGraphicsView {
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

    explicit Painter(QWidget *parent);

    ~Painter() override;

    // ------------------------------
    // Class interaction
    // ------------------------------

    void setupPainter(ObjectMgr *objectMgr, QLabel *label);

    [[maybe_unused]] Point *addPoint(int x, int y) const;

    [[maybe_unused]] Edge *addEdge(Point *start, Point *end) const;

    void updateInteractivity();

    [[nodiscard]] bool isMovingSpace() const;

    [[nodiscard]] QGraphicsItem *getSelectedItem() const { return m_selectedItem; }

    // ------------------------------
    // Class slots
    // ------------------------------
public slots:

    void setMovingSpace(bool moving);

    void clearContent() const;

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

    void updateSpacePosition() const;

private:
    // ------------------------------
    // Class fields
    // ------------------------------

    QGraphicsItem *m_selectedItem;
    bool m_isMovingSpace{};

    ObjectMgr *m_objectMgr{};
    QGraphicsScene *m_scene{};
    QLabel *m_label{};
};


#endif //APP_PAINTER_H
