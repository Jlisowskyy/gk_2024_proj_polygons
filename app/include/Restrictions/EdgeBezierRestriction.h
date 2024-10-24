//
// Created by Jlisowskyy on 14/10/24.
//

#ifndef APP_EDGEBEZIERRESTRICTION_H
#define APP_EDGEBEZIERRESTRICTION_H

/* internal includes */
#include "EdgeRestriction.h"
#include "../GraphicObjects/Point.h"

/* external includes */
#include <QGraphicsLineItem>
#include <QGraphicsPathItem>

class BezierPoint;

class EdgeBezierRestriction : public EdgeRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    using EdgeRestriction::EdgeRestriction;

    ~EdgeBezierRestriction() override = default;

    // ------------------------------
    // Abstract methods override
    // ------------------------------

    bool applyRestriction() final;

    std::string getIconName() override;

    void onRestrictionDelete() override;

    void onReposition() override;

    bool isRestrictionPreserved() final;

    QPointF tryToPreserveRestriction(size_t direction, QPointF dxdy) final;

    [[nodiscard]] BezierPoint *getDirectedBezierPoint(size_t direction) const;

    void setBezierPointMoving(BezierPoint *point) { m_bezierPoint = point; }

    [[nodiscard]] QLineF getPrevEdgeLine(size_t direction) const { return m_edgeLines[direction]; }

    void setBlockPropagation(bool blockPropagation) { m_blockPropagation = blockPropagation; }

    [[nodiscard]] bool getBlockPropagation() const { return m_blockPropagation; }

    // ------------------------------
    // protected methods
    // ------------------------------
protected:

    void _redrawBezierHelpingPoints();

    void _allocateBezierHelpingPoints();

    void _deallocateBezierHelpingPoints();

    void _drawBezierLine();

    void _fillBezierPath(QPainterPath &path);

    void _updateEdgeStorage();

    void _bezierPointMoved();

    void _bezierPointMoved(size_t direction);

    // ------------------------------
    // Class fields
    // ------------------------------

    BezierPoint *m_bezierPoint{};
    QGraphicsLineItem *m_line1{};
    BezierPoint *m_point1{};
    QGraphicsLineItem *m_line2{};
    BezierPoint *m_point2{};
    QGraphicsLineItem *m_line3{};

    QGraphicsPathItem *m_bezierLine{};

    QLineF m_edgeLines[2]{};

    bool m_blockPropagation{};
};

#endif //APP_EDGEBEZIERRESTRICTION_H
