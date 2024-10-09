//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_POINT_H
#define APP_POINT_H

/* internal includes */

/* external includes */
#include <QGraphicsEllipseItem>

class Point : public QGraphicsEllipseItem {
    // ------------------------------
    // Class constants
    // ------------------------------
public:
    static constexpr int POINT_RADIUS = 7;

    // ------------------------------
    // Class creation
    // ------------------------------

    explicit Point(int x, int y);

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] QPointF getPositionOnPainter() const;

    // ------------------------------
    // Private methods
    // ------------------------------

protected:
    // ------------------------------
    // Class fields
    // ------------------------------
};


#endif //APP_POINT_H
