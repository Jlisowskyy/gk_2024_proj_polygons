//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_POINT_H
#define APP_POINT_H

/* internal includes */
#include "../Constants.h"
#include "../Interfaces/IConnectableElement.h"
#include "../Interfaces/IPointPolygonObject.h"
#include "../ManagingObjects/Polygon.h"

/* external includes */
#include <QGraphicsEllipseItem>
#include <tuple>

/* Forward declaration */
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

    bool
    tryToPreserveRestrictions(const QPointF dxdy, const size_t direction, Point *blockPoint, const bool dryRun,
                              std::function<bool()> func) final;

    void moveWholePolygon(QPointF dxdy);

    bool areRestrictionsPreserved();

    void updateEdgePositions();

    template<typename ActionT>
    void iteratePoints(ActionT action);

    template<typename ActionT>
    void iterateEdges(ActionT action);

    [[nodiscard]] int getId() const { return m_pointId; }

    // ------------------------------
    // Private methods
    // ------------------------------
private:

    QVariant _onSelectionChange(const QVariant &value);

    QVariant _onPositionChanged(const QVariant &value);

    void _propagatePositionChange();

    void _fullPolygonPositionChange(QPointF dxdy);

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

template<typename ActionT>
void Point::iteratePoints(ActionT action) {
    Point *point = this;
    Q_ASSERT(point != nullptr);
    do {
        action(point);
        point = point->getConnectedPoint(LEFT);
    } while (point != this && point != nullptr);

    if (m_polygon->isFullPolygon()) {
        return;
    }

    point = this->getConnectedPoint(RIGHT);
    while (point != nullptr) {
        action(point);
        point = point->getConnectedPoint(RIGHT);
    }
}

template<typename ActionT>
void Point::iterateEdges(ActionT action) {
    Point *point = this;

    do {
        if (point->getConnectedElement(LEFT) == nullptr) {
            break;
        }

        action(point->getConnectedElement(LEFT));
        point = point->getConnectedPoint(LEFT);
    } while (point != this);

    if (m_polygon->isFullPolygon()) {
        return;
    }

    point = this;
    while (point != nullptr && point->getConnectedElement(RIGHT) != nullptr) {
        action(point->getConnectedElement(RIGHT));
        point = point->getConnectedPoint(RIGHT);
    }
}


#endif //APP_POINT_H
