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

    void setupToolBar(QToolBar *toolBar, Painter* painter, ObjectMgr *objectMgr);

// ------------------------------
// Class private methods
// ------------------------------
private:

    void addSeparator();
    void addToolbarLiteral(const char* strLiteral);
    QAction* addButtonToToolbar(const char* name, const char* imgPath, const char* toolTip, void (ToolBar::*func)());

// ------------------------------
// Class slots
// ------------------------------
public slots:

    void onCleanSpaceTriggered();
    void onAddVertexTriggered(bool isChecked) const;
    void onSetVerticalTriggered();
    void onSetHorizontalTriggered();
    void onSetConstLengthTriggered();
    void onSetBezierTriggered();
    void onSetContinuousCurveTriggered();
    void onDrawAlgorithmTriggered(bool isChecked) const;
    void onCutEdgeTriggered();
    void onMoveActionTriggered(bool isChecked) const;

private:
// ------------------------------
// Class fields
// ------------------------------

    QToolBar *m_toolBar{};
    Painter *m_painter{};
    ObjectMgr *m_objectMgr{};

    QAction *m_cleanSpaceAction{};
    QAction *m_addVertexAction{};
    QAction *m_setHorizontalAction{};
    QAction *m_setVerticalAction{};
    QAction *m_setConstLengthAction{};
    QAction *m_setBezierAction{};
    QAction *m_setContinuousAction{};
    QAction *m_cutEdgeAction{};
    QAction *m_drawAlgorithmAction{};
    QAction* m_moveAction{};
};


#endif //APP_TOOLBAR_H
