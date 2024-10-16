//
// Created by Jlisowskyy on 09/10/24.
//

#ifndef APP_POLYGON_H
#define APP_POLYGON_H

/* internal includes */
#include "../GraphicObjects/Edge.h"
#include "../GraphicObjects/Point.h"
#include "../GraphicObjects/DrawingWidget.h"

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

    void setupMgr(DrawingWidget *painter);

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

    void cutEdge();

    void setEdgeRestriction(const std::string &restrictionName);

    void setPointRestriction(const std::string &restrictionName);

    int getAndIncrementPointCount();

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
    DrawingWidget *m_drawingWidget{};

    Point *m_startingPoint{};
    Point *m_endingPoint{};

    int m_pointCount{};
};


#endif //APP_POLYGON_H
