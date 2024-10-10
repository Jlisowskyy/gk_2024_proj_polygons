//
// Created by Jlisowskyy on 09/10/24.
//

#ifndef APP_OBJECTMGR_H
#define APP_OBJECTMGR_H

/* internal includes */
#include "Edge.h"
#include "Point.h"
#include "Painter.h"

/* external includes */
#include <vector>
#include <QObject>
#include <tuple>

class ObjectMgr : public QObject {
Q_OBJECT
    // ------------------------------
    // Class constants
    // ------------------------------
public:
    static constexpr int FINAL_POINT_HIT_BOX_SIZE = 20;

    // ------------------------------
    // Class creation
    // ------------------------------

    explicit ObjectMgr(QObject *parent);

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

    // ------------------------------
    // Private methods
    // ------------------------------
private:
    [[nodiscard]] Point *findPointSpot(int x, int y) const;

    // ------------------------------
    // Class fields
    // ------------------------------

protected:
    bool m_isAddingVertices{};
    Painter *m_painter{};
    std::vector<Point *> m_points{};
    std::vector<Edge *> m_edges{};
};


#endif //APP_OBJECTMGR_H
