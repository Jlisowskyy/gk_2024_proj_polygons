//
// Created by Jlisowskyy on 08/10/24.
//

/* external includes */
#include <QDebug>

/* internal includes */
#include "ToolBar.h"
#include "../GraphicObjects/Point.h"
#include "../GraphicObjects/Edge.h"

#define EDGE_TOOLTIP_STR(str) str" for selected edge"
#define EDGE_CONSTRAINT_TOOLTIP_STR(str) "Set " EDGE_TOOLTIP_STR(str " constraint")

#define VERTEX_TOOLTIP_STR(str) str" for selected vertex"
#define VERTEX_CONSTRAINT_TOOLTIP_STR(str) "Set " VERTEX_TOOLTIP_STR(str " constraint")

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

void ToolBar::setupToolBar(QToolBar *toolBar) {
    Q_ASSERT(toolBar != nullptr);
    Q_ASSERT(m_toolBar == nullptr);
    m_toolBar = toolBar;

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

    m_moveAction = _addButtonToToolbar(
            "Move space",
            ":/icons/move.png",
            "Move the whole space around"
    );
    m_moveAction->setCheckable(true);
    m_moveAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));

    _addSeparator();

    /* Edge actions */
    _addToolbarLiteral("Edge:");
    m_setVerticalAction = _addButtonToToolbar(
            "Vertical constraint",
            ":/icons/vertical.png",
            EDGE_CONSTRAINT_TOOLTIP_STR("vertical constraint")
    );

    m_setHorizontalAction = _addButtonToToolbar(
            "Horizontal constraint",
            ":/icons/horizontal.png",
            EDGE_CONSTRAINT_TOOLTIP_STR("horizontal constraint")
    );

    m_setConstLengthAction = _addButtonToToolbar(
            "Const length constraint",
            ":/icons/const_length.png",
            EDGE_CONSTRAINT_TOOLTIP_STR("const length")
    );

    m_setBezierAction = _addButtonToToolbar(
            "Bezier edge",
            ":/icons/bezier.png",
            "Enable Bezier Curve for selected edge"
    );

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

    _addSeparator();

    /* Vertex actions */
    _addToolbarLiteral("Vertex:");

    m_setContinuousAction = _addButtonToToolbar(
            "Continuous curve constraint",
            ":/icons/cont.png",
            VERTEX_CONSTRAINT_TOOLTIP_STR("Continuous curve")
    );

    _setEdgeButtonsIsDisabledState(true);
    _setVertexButtonsIsDisabledState(true);
}

void ToolBar::_setEdgeButtonsIsDisabledState(bool isDisabled) {
    m_setVerticalAction->setDisabled(isDisabled);
    m_setHorizontalAction->setDisabled(isDisabled);
    m_setConstLengthAction->setDisabled(isDisabled);
    m_setBezierAction->setDisabled(isDisabled);
    m_cutEdgeAction->setDisabled(isDisabled);
}

void ToolBar::_setVertexButtonsIsDisabledState(bool isDisabled) {
    m_setContinuousAction->setDisabled(isDisabled);
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
