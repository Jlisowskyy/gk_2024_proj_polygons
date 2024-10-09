//
// Created by Jlisowskyy on 08/10/24.
//

/* external includes */
#include <QDebug>

/* internal includes */
#include "ToolBar.h"

#define EDGE_TOOLTIP_STR(str) str" for selected edge"
#define EDGE_CONSTRAINT_TOOLTIP_STR(str) "Set " EDGE_TOOLTIP_STR(str " constraint")

#define VERTEX_TOOLTIP_STR(str) str" for selected vertex"
#define VERTEX_CONSTRAINT_TOOLTIP_STR(str) "Set " VERTEX_TOOLTIP_STR(str " constraint")

ToolBar::ToolBar(QObject *parent) : QObject(parent) {
}

ToolBar::~ToolBar() {
}

void ToolBar::addToolbarLiteral(const char *strLiteral) {
    auto literal = new QAction(tr(strLiteral), m_toolBar);
    literal->setDisabled(true);
    m_toolBar->addAction(literal);
}

QAction *
ToolBar::addButtonToToolbar(const char *name, const char *imgPath, const char *toolTip,
                            void (ToolBar::*func)() = nullptr) {
    auto button = new QAction(tr(name), m_toolBar);
    button->setIcon(QIcon(imgPath));
    button->setToolTip(tr(toolTip));
    m_toolBar->addAction(button);

    if (func != nullptr) {
        connect(button, &QAction::triggered, this, func);
    }

    return button;
}

void ToolBar::addSeparator() {
    auto literal = new QAction(m_toolBar);
    literal->setSeparator(true);
    m_toolBar->addAction(literal);
}

void ToolBar::setupToolBar(QToolBar *toolBar, Painter *painter, ObjectMgr *objectMgr) {
    Q_ASSERT(toolBar != nullptr);
    Q_ASSERT(m_toolBar == nullptr);
    m_toolBar = toolBar;

    Q_ASSERT(objectMgr != nullptr);
    Q_ASSERT(m_objectMgr == nullptr);
    m_objectMgr = objectMgr;

    Q_ASSERT(painter != nullptr);
    Q_ASSERT(m_painter == nullptr);
    m_painter = painter;

    /* General space functionalities: */
    addToolbarLiteral("Space:");
    m_cleanSpaceAction = addButtonToToolbar(
        "Clean space",
        ":/icons/trash.png",
        "Remove all objects from the space",
        &ToolBar::onCleanSpaceTriggered
    );

    m_addVertexAction = addButtonToToolbar(
        "Place vertex",
        ":/icons/add_vertex.png",
        "Add vertex tool"
    );
    m_addVertexAction->setCheckable(true);
    connect(m_addVertexAction, &QAction::triggered, this, &ToolBar::onAddVertexTriggered);

    addSeparator();

    /* Edge actions */
    addToolbarLiteral("Edge:");
    m_setVerticalAction = addButtonToToolbar(
        "Vertical constraint",
        ":/icons/vertical.png",
        EDGE_CONSTRAINT_TOOLTIP_STR("vertical constraint"),
        &ToolBar::onSetVerticalTriggered
    );

    m_setHorizontalAction = addButtonToToolbar(
        "Horizontal constraint",
        ":/icons/horizontal.png",
        EDGE_CONSTRAINT_TOOLTIP_STR("horizontal constraint"),
        &ToolBar::onSetHorizontalTriggered
    );

    m_setConstLengthAction = addButtonToToolbar(
        "Const length constraint",
        ":/icons/const_length.png",
        EDGE_CONSTRAINT_TOOLTIP_STR("const length"),
        &ToolBar::onSetConstLengthTriggered
    );

    m_setBezierAction = addButtonToToolbar(
        "Bezier edge",
        ":/icons/bezier.png",
        "Enable Bezier Curve for selected edge",
        &ToolBar::onSetBezierTriggered
    );

    m_drawAlgorithmAction = addButtonToToolbar(
        "Draw algorithm",
        ":/icons/draw_algo.png",
        "Enable custom draw algorithm"
    );
    m_drawAlgorithmAction->setCheckable(true);
    connect(m_drawAlgorithmAction, &QAction::triggered, this, &ToolBar::onDrawAlgorithmTriggered);

    m_cutEdgeAction = addButtonToToolbar(
        "Cut edge",
        ":/icons/cut_edge.png",
        "Cut the selected edge",
        &ToolBar::onCutEdgeTriggered
    );

    addSeparator();

    /* Vertex actions */
    addToolbarLiteral("Vertex:");

    m_setContinuousAction = addButtonToToolbar(
        "Continuous curve constraint",
        ":/icons/cont.png",
        VERTEX_CONSTRAINT_TOOLTIP_STR("Continuous curve"),
        &ToolBar::onSetContinuousCurveTriggered
    );
}

void ToolBar::onCleanSpaceTriggered() {
    qDebug() << "onCleanSpaceTriggered";

    m_objectMgr->clearItems();
}

void ToolBar::onAddVertexTriggered(const bool isChecked) const {
    qDebug() << "onAddVertexTriggered";

    m_objectMgr->setIsAddingVertices(isChecked);
    m_painter->setInteractive(!isChecked);
}

void ToolBar::onSetVerticalTriggered() {
    qDebug() << "onSetVerticalTriggered";
}

void ToolBar::onSetHorizontalTriggered() {
    qDebug() << "onSetHorizontalTriggered";
}

void ToolBar::onSetConstLengthTriggered() {
    qDebug() << "onSetConstLengthTriggered";
}

void ToolBar::onSetBezierTriggered() {
    qDebug() << "onSetBezierTriggered";
}

void ToolBar::onSetContinuousCurveTriggered() {
    qDebug() << "onSetContinuousCurveTriggered";
}

void ToolBar::onDrawAlgorithmTriggered(bool isChecked) const {
    qDebug() << "onDrawAlgorithmTriggered";
}

void ToolBar::onCutEdgeTriggered() {
    qDebug() << "onCutEdgeTriggered";
}
