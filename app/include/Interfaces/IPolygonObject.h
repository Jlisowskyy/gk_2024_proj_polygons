//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_IPOLYGONOBJECT_H
#define APP_IPOLYGONOBJECT_H

/* external includes */
#include <tuple>
#include <QPointF>

/* Forward declaration */
class Point;

class DrawingWidget;

class ObjectRestriction;

class Polygon;

class IPolygonObject {
    // ------------------------------
    // Class creation
    // ------------------------------
public:
    explicit IPolygonObject(Polygon *polygon);

    virtual ~IPolygonObject() = default;

    // ------------------------------
    // Class interaction
    // ------------------------------

    virtual bool applyRestriction(ObjectRestriction *restriction, DrawingWidget *drawingWidget);

    [[nodiscard]] ObjectRestriction *getRestriction() const;

    void cleanRestriction();

    // ------------------------------
    // Abstract methods
    // ------------------------------

    virtual std::tuple<Point *, Point *> remove(bool isFullPolygon, DrawingWidget *painter) = 0;

    // ------------------------------
    // Protected methods
    // ------------------------------
protected:
    void onRemoved();

    // ------------------------------
    // Static methods
    // ------------------------------

    static void _addEdgeIfNotTriangle(Point **connections, bool isFullPolygon, DrawingWidget *painter);

    [[nodiscard]] static std::tuple<Point *, Point *>
    _prepareNewAttachmentPoints(Point **connections, bool isFullPolygon);

    // ------------------------------
    // Class fields
    // ------------------------------

    ObjectRestriction *m_restriction{};
    Polygon *m_polygon{};
};

#endif //APP_IPOLYGONOBJECT_H
