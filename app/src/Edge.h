//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_EDGE_H
#define APP_EDGE_H

/* internal includes */
#include "Point.h"

/* external includes */
#include <QGraphicsLineItem>

class Edge : public QGraphicsLineItem {
// ------------------------------
// Class constants
// ------------------------------
public:

    static constexpr int LINE_WIDTH = 5;

// ------------------------------
// Class creation
// ------------------------------

    explicit Edge(Point* start, Point* end);

// ------------------------------
// Class interaction
// ------------------------------

// ------------------------------
// Private methods
// ------------------------------

protected:

// ------------------------------
// Class fields
// ------------------------------

    Point* m_start{};
    Point* m_end{};
};


#endif //APP_EDGE_H
