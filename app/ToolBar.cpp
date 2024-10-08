//
// Created by Jlisowskyy on 08/10/24.
//

#include "ToolBar.h"

#define EDGE_TOOLTIP_STR(str) str" for selected edge"
#define EDGE_CONSTRAINT_TOOLTIP_STR(str) "Set " EDGE_TOOLTIP_STR(str " constraint")

#define VERTEX_TOOLTIP_STR(str) str" for selected vertex"
#define VERTEX_CONSTRAINT_TOOLTIP_STR(str) "Set " VERTEX_TOOLTIP_STR(str " constraint")

ToolBar::ToolBar(QObject *parent) : QObject(parent), m_toolBar(nullptr) {

}

ToolBar::~ToolBar() {

}

void ToolBar::addToolbarLiteral(const char *strLiteral) {
    auto literal = new QAction(tr(strLiteral), m_toolBar);
    literal->setDisabled(true);
    m_toolBar->addAction(literal);
}

void ToolBar::addButtonToToolbar(const char *name, const char *imgPath, const char *toolTip) {
    auto button = new QAction(tr(name), m_toolBar);
    button->setIcon(QIcon(imgPath));
    button->setToolTip(tr(toolTip));
    m_toolBar->addAction(button);
}

void ToolBar::setupToolBar(QToolBar *toolBar) {
    Q_ASSERT(toolBar != nullptr);
    m_toolBar = toolBar;

    /* General space functionalities: */
    addToolbarLiteral("Space functions:");
    addButtonToToolbar("Clean space", ":/icons/trash.png", "Remove all objects from the space");
    addButtonToToolbar("Place vertex", ":/icons/add_vertex.png", "Add vertex tool");

    addToolbarLiteral("|");

    /* Edge actions */
    addToolbarLiteral("Edge functions:");
    addButtonToToolbar("Vertical constraint", ":/icons/vertical.png",
                       EDGE_CONSTRAINT_TOOLTIP_STR("vertical constraint"));
    addButtonToToolbar("Horizontal constraint", ":/icons/horizontal.png",
                       EDGE_CONSTRAINT_TOOLTIP_STR("horizontal constraint"));
    addButtonToToolbar("Const length constraint", ":/icons/const_length.png",
                       EDGE_CONSTRAINT_TOOLTIP_STR("const length"));
    addButtonToToolbar("Bezier edge", ":/icons/bezier.png", "Enable Bezier Curve for selected edge");

    addToolbarLiteral("|");

    /* Vertex actions */
    addToolbarLiteral("Vertex functions:");
    addButtonToToolbar("Continuous curve constraint", ":/icons/cont.png",
                       VERTEX_CONSTRAINT_TOOLTIP_STR("Continuous curve"));
}
