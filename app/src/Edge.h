//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_EDGE_H
#define APP_EDGE_H

/* internal includes */
#include "Point.h"

/* external includes */
#include <QGraphicsLineItem>
#include <tuple>

/* Forward declaration */
class ObjectMgr;

class Edge : public QGraphicsLineItem, public IConnectableElement<Point> {
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

    std::tuple<Point*, Point*> remove(bool isFullPolygon, Painter *painter);

    // ------------------------------
    // Private methods
    // ------------------------------
private:

    QVariant _onSelectionChange(const QVariant &value);

    QVariant _onPositionChange(const QVariant &value);

    QVariant _onPositionChanged(const QVariant &value);


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
