//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_TOOLBAR_H
#define APP_TOOLBAR_H

/* internal includes */
#include "Painter.h"
#include "ObjectMgr.h"

/* external includes */
#include <QObject>
#include <QToolBar>
#include <QGraphicsItem>

class ToolBar : public QObject {
    Q_OBJECT

    // ------------------------------
    // Class creation
    // ------------------------------

public:
    explicit ToolBar(QObject *parent);

    ~ToolBar() override;

    // ------------------------------
    // Class interaction
    // ------------------------------

    void setupToolBar(QToolBar *toolBar);

    // ------------------------------
    // Class slots
    // ------------------------------
public slots:

    void selectionChanged(QGraphicsItem *item);

    // ------------------------------
    // Class private methods
    // ------------------------------
private:
    void addSeparator();

    void addToolbarLiteral(const char *strLiteral);

    QAction *addButtonToToolbar(const char *name, const char *imgPath, const char *toolTip);

    void setEdgeButtonsIsDisabledState(bool isDisabled);
    void setVertexButtonsIsDisabledState(bool isDisabled);

// ------------------------------
// Public fields
// ------------------------------
public:

    QAction *m_cleanSpaceAction{};
    QAction *m_addVertexAction{};
    QAction *m_setHorizontalAction{};
    QAction *m_setVerticalAction{};
    QAction *m_setConstLengthAction{};
    QAction *m_setBezierAction{};
    QAction *m_setContinuousAction{};
    QAction *m_cutEdgeAction{};
    QAction *m_drawAlgorithmAction{};
    QAction *m_moveAction{};

protected:
    // ------------------------------
    // Class fields
    // ------------------------------

    QToolBar *m_toolBar{};
};


#endif //APP_TOOLBAR_H
