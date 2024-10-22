//
// Created by Jlisowskyy on 14/10/24.
//

#ifndef APP_EDGEBEZIERRESTRICTION_H
#define APP_EDGEBEZIERRESTRICTION_H

/* internal includes */
#include "EdgeRestriction.h"

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

    BezierPoint *getDirectedBezierPoint(size_t direction) const;

    // ------------------------------
    // protected methods
    // ------------------------------
protected:

    void _redrawBezierHelpingPoints();

    void _allocateBezierHelpingPoints();

    void _deallocateBezierHelpingPoints();

    void _drawBezierLine();

    void _fillBezierPath(QPainterPath& path);

    // ------------------------------
    // Class fields
    // ------------------------------

    QGraphicsLineItem *m_line1{};
    BezierPoint *m_point1{};
    QGraphicsLineItem *m_line2{};
    BezierPoint *m_point2{};
    QGraphicsLineItem *m_line3{};

    QGraphicsPathItem *m_bezierLine{};
};

#endif //APP_EDGEBEZIERRESTRICTION_H
