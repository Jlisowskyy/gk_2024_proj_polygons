//
// Created by Jlisowskyy on 14/10/24.
//

#ifndef APP_BEZIERPOINT_H
#define APP_BEZIERPOINT_H

/* external includes */
#include <QGraphicsEllipseItem>
#include <QPointF>

class EdgeBezierRestriction;

class BezierPoint : public QGraphicsEllipseItem {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit BezierPoint(int x, int y);

    ~BezierPoint() override = default;

    // ------------------------------
    // Class interaction
    // ------------------------------

    [[nodiscard]] QPointF getPositionOnPainter() const;

    void setPositionOnPainter(const QPointF &position);

    QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    void setEdgeBezierRestriction(EdgeBezierRestriction *edgeBezierRestriction) {
        Q_ASSERT(edgeBezierRestriction != nullptr);
        m_edgeBezierRestriction = edgeBezierRestriction;
    }

    [[nodiscard]] QPointF getPrevPos() const {
        return m_prevPos;
    }

    // ------------------------------
    // Protected methods
    // ------------------------------
protected:

    void _onPositionChange();

    // ------------------------------
    // Class fields
    // ------------------------------

    EdgeBezierRestriction *m_edgeBezierRestriction{};

    QPointF m_prevPos{};
};

#endif //APP_BEZIERPOINT_H
