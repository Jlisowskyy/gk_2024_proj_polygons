//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_TOOLBAR_H
#define APP_TOOLBAR_H

#include "QObject"
#include "QToolBar"

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
    void onAddVertexTriggered(bool isChecked);
    void onSetVerticalTriggered();
    void onSetHorizontalTriggered();
    void onSetConstLengthTriggered();
    void onSetBezierTriggered();
    void onsetContinuousCurveTriggered();

private:
// ------------------------------
// Class fields
// ------------------------------

    QToolBar *m_toolBar{};
    QAction *m_cleanSpaceAction{};
    QAction *m_addVertexAction{};
    QAction *m_setHorizontalAction{};
    QAction *m_setVerticalAction{};
    QAction *m_setConstLengthAction{};
    QAction *m_setBezierAction{};
    QAction *m_setContinuousAction{};
};


#endif //APP_TOOLBAR_H
