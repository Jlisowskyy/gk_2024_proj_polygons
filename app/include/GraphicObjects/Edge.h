//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_EDGE_H
#define APP_EDGE_H

/* internal includes */
#include "Point.h"
#include "../Interfaces/IEdgePolygonObject.h"

/* external includes */
#include <QGraphicsLineItem>
#include <tuple>
#include <QPoint>

/* Forward declaration */
class Polygon;

class DrawingWidget;

class Edge : public QGraphicsLineItem, public IConnectableElement<Point>, public IEdgePolygonObject {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit Edge(Point *start, Point *end, DrawingWidget *drawingWidget, Polygon *polygon);

    ~Edge() override = default;

    // ------------------------------
    // Class interaction
    // ------------------------------

    void repositionByPoints();

    void cutEdge(DrawingWidget *drawingWidget);

    [[nodiscard]] QPointF getMidPoint() const;

    [[nodiscard]] double getLength() const;

    // ------------------------------
    // Private methods
    // ------------------------------
private:

    QVariant _onSelectionChange(const QVariant &value);

    QVariant _onPositionChange(const QVariant &value);

    QVariant _onPositionChanged(const QVariant &value);

    void _bresenhamLine(QPainter *painter);

    void _propagatePositionChange(QPointF point);

    // ------------------------------
    // Protected Methods
    // ------------------------------
protected:

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // ------------------------------
    // Class fields
    // ------------------------------

    DrawingWidget *m_drawingWidget{};
    bool m_isUpdating{};
};


#endif //APP_EDGE_H
