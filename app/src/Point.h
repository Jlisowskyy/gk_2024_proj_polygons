//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_POINT_H
#define APP_POINT_H

/* internal includes */
#include "Constants.h"

/* external includes */
#include <QGraphicsEllipseItem>

/* Forward declaration */
class ObjectMgr;

class Edge;

class Point : public QGraphicsEllipseItem {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit Point(int x, int y);

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] QPointF getPositionOnPainter() const;

    [[nodiscard]] ConnectionType getEdgeType(Edge *edge);

    [[nodiscard]] Edge *getConnectedEdge(ConnectionType type) const;

    void setConnectedEdge(ConnectionType type, Edge *edge);

    [[nodiscard]] double getRadius() const;

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

    Edge *m_edges[MAX_CONNECTIONS]{};
};


#endif //APP_POINT_H
