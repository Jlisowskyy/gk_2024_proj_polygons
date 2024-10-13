//
// Created by Jlisowskyy on 09/10/24.
//

#ifndef APP_POLYGON_H
#define APP_POLYGON_H

/* internal includes */
#include "Edge.h"
#include "Point.h"
#include "Painter.h"

/* external includes */
#include <vector>
#include <QObject>
#include <tuple>

class Polygon : public QObject {
Q_OBJECT
    // ------------------------------
    // Class constants
    // ------------------------------
public:
    static constexpr int FINAL_POINT_HIT_BOX_SIZE = 20;

    // ------------------------------
    // Class creation
    // ------------------------------

    explicit Polygon(QObject *parent);

    // ------------------------------
    // Class interaction
    // ------------------------------

    void setupMgr(Painter *painter);

    void addPoint(int x, int y);

    [[nodiscard]] bool getIsAddingVertices() const;

    [[nodiscard]] bool isFullPolygon() const;

    // ------------------------------
    // Class slots
    // ------------------------------
public slots:

    void clearItems();

    void setIsAddingVertices(bool value);

    void removeSelection();

    // ------------------------------
    // Private methods
    // ------------------------------
private:
    [[nodiscard]] Point *_findPointSpot(int x, int y) const;

    // ------------------------------
    // Class fields
    // ------------------------------

protected:
    bool m_isAddingVertices{};
    Painter *m_painter{};

    Point *m_startingPoint{};
    Point *m_endingPoint{};
};


#endif //APP_POLYGON_H
