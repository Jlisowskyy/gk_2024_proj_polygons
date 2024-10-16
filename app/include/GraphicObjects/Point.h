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

    explicit Point(int x, int y, Polygon *polygon);

    ~Point() override = default;

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] QPointF getPositionOnPainter() const;

    void setPositionOnPainter(const QPointF &position);

    [[nodiscard]] double getRadius() const;

    [[nodiscard]] Point *getConnectedPoint(size_t direction) const;

    [[nodiscard]] Point *getDistantPoint(size_t direction, uint distance) const;

    [[nodiscard]] int countPoints();

    bool tryToPreserveRestrictions(const QPointF dxdy, const size_t direction, Point *blockPoint, bool dryRun) final;

    void moveWholePolygon(QPointF dxdy);

    bool areRestrictionsPreserved();

    void updateEdgePositions();

    // ------------------------------
    // Private methods
    // ------------------------------
private:

    QVariant _onSelectionChange(const QVariant &value);

    QVariant _onPositionChanged(const QVariant &value);

    void _propagatePositionChange();

    [[nodiscard]] int _countPoints(Point *startPoint);

    void _fullPolygonPositionChange(QPointF dxdy);

    void _moveWholePolygon(Point* startPoint, QPointF dxdy);

    void _updateEdgePositions(Point *startPoint, size_t direction);

    // ------------------------------
    // Protected Methods
    // ------------------------------
protected:

    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

    // ------------------------------
    // Class fields
    // ------------------------------

    const int m_pointId;
    QPointF m_prevPos{};
};


#endif //APP_POINT_H
