//
// Created by Jlisowskyy on 08/10/24.
//

/* external includes */
#include <QDebug>

/* internal includes */
#include "../include/ManagingObjects/ToolBar.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/Edge.h"
#include "../include/ManagingObjects/Polygon.h"
#include "../include/Restrictions/Restrictions.h"
#include "../include/GraphicObjects/DebugDialog.h"
#include "../include/GraphicObjects/DrawingWidget.h"
#include "../include/Restrictions/EdgeBezierRestriction.h"

#include <string>

#include <string>

inline std::string EdgeRestrictionName(const char *str) {
    return std::string(str) + " edge restriction";
}

inline std::string EdgeTooltipStr(const char *str) {
    return std::string(str) + " for selected edge";
}

inline std::string EdgeRestrictionTooltipStr(const char *str) {
    return "Set " + EdgeTooltipStr(str) + " restriction";
}

inline std::string PointRestrictionName(const char *str) {
    return std::string(str) + " point restriction";
}

inline std::string PointTooltipStr(const char *str) {
    return std::string(str) + " for selected point";
}

inline std::string PointRestrictionTooltipStr(const char *str) {
    return "Set " + PointTooltipStr(str) + " restriction";
}


ToolBar::ToolBar(QObject *parent) : QObject(parent) {
}

ToolBar::~ToolBar() {
}

void ToolBar::_addToolbarLiteral(const char *strLiteral) {
    auto literal = new QAction(tr(strLiteral), m_toolBar);
    literal->setDisabled(true);
    m_toolBar->addAction(literal);
}

QAction *
ToolBar::_addButtonToToolbar(const char *name, const char *imgPath, const char *toolTip) {
    auto button = new QAction(tr(name), m_toolBar);
    button->setIcon(QIcon(imgPath));
    button->setToolTip(tr(toolTip));
    m_toolBar->addAction(button);

    return button;
}

void ToolBar::_addSeparator() {
    auto literal = new QAction(m_toolBar);
    literal->setSeparator(true);
    m_toolBar->addAction(literal);
}

void ToolBar::setupToolBar(QToolBar *toolBar, Polygon *polygon, DrawingWidget *drawingWidget) {
    Q_ASSERT(toolBar != nullptr);
    Q_ASSERT(m_toolBar == nullptr);
    m_toolBar = toolBar;

    Q_ASSERT(m_drawingWidget == nullptr);
    Q_ASSERT(drawingWidget != nullptr);
    m_drawingWidget = drawingWidget;

    /* General space functionalities: */
    _addToolbarLiteral("Space:");
    m_cleanSpaceAction = _addButtonToToolbar(
            "Clean space",
            ":/icons/trash.png",
            "Remove all objects from the space"
    );
    m_cleanSpaceAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Delete));

    m_addVertexAction = _addButtonToToolbar(
            "Place vertex",
            ":/icons/add_vertex.png",
            "Add vertex tool"
    );
    m_addVertexAction->setCheckable(true);
    m_addVertexAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_V));

    m_moveAction = _addButtonToToolbar(
            "Move space",
            ":/icons/move.png",
            "Move the whole space around"
    );
    m_moveAction->setCheckable(true);
    m_moveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));

    m_debug = _addButtonToToolbar(
            "Debug",
            ":/icons/debug.png",
            "Move the polygon"
    );
    m_debug->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    connect(m_debug, &QAction::triggered, [polygon]() {
        VertexInputDialog dialog(nullptr);
        if (dialog.exec() == QDialog::Accepted) {
            int vertexIdx = dialog.getVertexIdx();
            QPointF moveBy = dialog.getMoveBy();

            qDebug() << "----------- DEBUG RUN-----------";
            polygon->moveVertex(vertexIdx, moveBy);
        }
    });

    _addSeparator();

    /* Edge actions */
    _addToolbarLiteral("Edge:");

    m_drawAlgorithmAction = _addButtonToToolbar(
            "Draw algorithm",
            ":/icons/draw_algo.png",
            "Enable custom draw algorithm"
    );
    m_drawAlgorithmAction->setCheckable(true);

    m_cutEdgeAction = _addButtonToToolbar(
            "Cut edge",
            ":/icons/cut_edge.png",
            "Cut the selected edge"
    );

    m_setHorizontalAction = _addEdgeRestrictionButton(polygon, "horizontal");
    m_setVerticalAction = _addEdgeRestrictionButton(polygon, "vertical");
    m_setConstLengthAction = _addEdgeRestrictionButton(polygon, "const_length");
    m_setBezierAction = _addEdgeRestrictionButton(polygon, "bezier");

    _addSeparator();

    /* Vertex actions */
    _addToolbarLiteral("Vertex:");

    m_setGContinuousAction = _addPointRestrictionButton(polygon, "g_continuous");
    m_setG1ContinuousAction = _addPointRestrictionButton(polygon, "g1_continuous");
    m_setC1ContinuousAction = _addPointRestrictionButton(polygon, "c1_continuous");

    _setEdgeButtonsIsDisabledState(true);
    _setVertexButtonsIsDisabledState(true);
}

void ToolBar::_setEdgeButtonsIsDisabledState(bool isDisabled) {
    m_setHorizontalAction->setDisabled(isDisabled);
    m_setBezierAction->setDisabled(isDisabled);
    m_cutEdgeAction->setDisabled(isDisabled);
    m_setVerticalAction->setDisabled(isDisabled);
    m_setConstLengthAction->setDisabled(isDisabled);
}

void ToolBar::_setVertexButtonsIsDisabledState(bool isDisabled) {
    if (isDisabled) {
        m_setG1ContinuousAction->setDisabled(isDisabled);
        m_setC1ContinuousAction->setDisabled(isDisabled);
        m_setGContinuousAction->setDisabled(isDisabled);
    } else if (Point *point = m_drawingWidget->getSelectedPoint()) {
        Edge *edges[] = {point->getConnectedElement(LEFT), point->getConnectedElement(RIGHT)};

        bool isNeighborBezier = false;
        for (Edge *edge: edges) {
            isNeighborBezier |=
                    edge != nullptr && dynamic_cast<EdgeBezierRestriction *>(edge->getRestriction()) != nullptr;
        }

        m_setG1ContinuousAction->setDisabled(!isNeighborBezier);
        m_setC1ContinuousAction->setDisabled(!isNeighborBezier);
        m_setGContinuousAction->setDisabled(!isNeighborBezier);
    }


}

void ToolBar::selectionChanged(QGraphicsItem *item) {
    if (auto *point = dynamic_cast<Point *>(item); point != nullptr) {
        _setVertexButtonsIsDisabledState(false);
        _setEdgeButtonsIsDisabledState(true);
    } else if (auto *edge = dynamic_cast<Edge *>(item); edge != nullptr) {
        _setVertexButtonsIsDisabledState(true);
        _setEdgeButtonsIsDisabledState(false);
    } else {
        _setVertexButtonsIsDisabledState(true);
        _setEdgeButtonsIsDisabledState(true);
    }
}

QAction *ToolBar::_addEdgeRestrictionButton(Polygon *polygon, const char *restrictionName) {
    QAction *ptr = _addButtonToToolbar(
            EdgeRestrictionName(restrictionName).c_str(),
            EdgeRestrictionIconPath(restrictionName).c_str(),
            EdgeRestrictionTooltipStr(restrictionName).c_str()
    );

    connect(ptr, &QAction::triggered, [polygon, restrictionName]() {
        polygon->setEdgeRestriction(restrictionName);
    });

    return ptr;
}

QAction *ToolBar::_addPointRestrictionButton(Polygon *polygon, const char *restrictionName) {
    QAction *ptr = _addButtonToToolbar(
            PointRestrictionName(restrictionName).c_str(),
            PointIconRestrictionPath(restrictionName).c_str(),
            PointRestrictionTooltipStr(restrictionName).c_str()
    );

    connect(ptr, &QAction::triggered, [polygon, restrictionName]() {
        polygon->setPointRestriction(restrictionName);
    });

    return ptr;
}
