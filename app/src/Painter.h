//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_PAINTER_H
#define APP_PAINTER_H

/* external includes */
#include <QObject>
#include <QGraphicsView>
#include <QMouseEvent>
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
    static constexpr int POINT_RADIUS = 5;

// ------------------------------
// Class creation
// ------------------------------

    explicit Painter(QWidget *parent);

    ~Painter() override;

// ------------------------------
// Class interaction
// ------------------------------

    void setupPainter(ObjectMgr *objectMgr);

    [[maybe_unused]] Point *addPoint(int x, int y) const;

    [[maybe_unused]] Edge *addEdge(Point *start, Point *end) const;

    void clearContent() const;

// ------------------------------
// Protected methods
// ------------------------------
protected:

    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

// ------------------------------
// Private methods
// ------------------------------
private:

// ------------------------------
// Class fields
// ------------------------------

    ObjectMgr *m_objectMgr{};
    QGraphicsScene *m_scene{};
};


#endif //APP_PAINTER_H
