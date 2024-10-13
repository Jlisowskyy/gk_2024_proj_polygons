//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_POINT_H
#define APP_POINT_H

/* internal includes */
#include "../Constants.h"
#include "../Interfaces/IConnectableElement.h"
#include "../Interfaces/IPointPolygonObject.h"

/* external includes */
#include <QGraphicsEllipseItem>
#include <tuple>

/* Forward declaration */
class Polygon;

class Edge;

class DrawingWidget;

class Point : public QGraphicsEllipseItem, public IConnectableElement<Edge>, public IPointPolygonObject {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit Point(int x, int y);

    ~Point() override = default;

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] QPointF getPositionOnPainter() const;

    [[nodiscard]] double getRadius() const;

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
};


#endif //APP_POINT_H
