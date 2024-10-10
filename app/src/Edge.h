//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_EDGE_H
#define APP_EDGE_H

/* internal includes */
#include "Point.h"

/* external includes */
#include <QGraphicsLineItem>

/* Forward declaration */
class ObjectMgr;

class Edge : public QGraphicsLineItem {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit Edge(Point *start, Point *end);

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] bool isRightConnected(Point *point) const {
        return point != nullptr && m_connections[RIGHT] == point;
    }

    [[nodiscard]] bool isLeftConnected(Point *point) const {
        return point != nullptr && m_connections[LEFT] == point;
    }

    [[nodiscard]] bool isConnected(Point *point) const {
        return isLeftConnected(point) || isRightConnected(point);
    }

    void repositionByPoints();

    // ------------------------------
    // Private methods
    // ------------------------------
private:

    QVariant onSelectionChange(const QVariant &value);

    QVariant onPositionChange(const QVariant &value);

    QVariant onPositionChanged(const QVariant &value);


    // ------------------------------
    // Protected Methods
    // ------------------------------
protected:

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // ------------------------------
    // Class fields
    // ------------------------------

    bool m_isUpdating{};
    Point *m_connections[MAX_CONNECTIONS]{};
};


#endif //APP_EDGE_H
