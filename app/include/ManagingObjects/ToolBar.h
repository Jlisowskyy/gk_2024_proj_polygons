//
// Created by Jlisowskyy on 08/10/24.
//

#ifndef APP_TOOLBAR_H
#define APP_TOOLBAR_H

/* internal includes */

/* external includes */
#include <QObject>
#include <QToolBar>
#include <QGraphicsItem>

/* Forward declaration */
class Polygon;

class DrawingWidget;

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

    void setupToolBar(QToolBar *toolBar, Polygon *polygon, DrawingWidget *drawingWidget);

    // ------------------------------
    // Class slots
    // ------------------------------
public slots:

    void selectionChanged(QGraphicsItem *item);

    // ------------------------------
    // Class private methods
    // ------------------------------
private:
    void _addSeparator();

    void _addToolbarLiteral(const char *strLiteral);

    QAction *_addButtonToToolbar(const char *name, const char *imgPath, const char *toolTip);

    void _setEdgeButtonsIsDisabledState(bool isDisabled);

    void _setVertexButtonsIsDisabledState(bool isDisabled);

    QAction *_addEdgeRestrictionButton(Polygon *polygon, const char *restrictionName);

    QAction *_addPointRestrictionButton(Polygon *polygon, const char *restrictionName);

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
    QAction *m_setGContinuousAction{};
    QAction *m_cutEdgeAction{};
    QAction *m_drawAlgorithmAction{};
    QAction *m_moveAction{};
    QAction *m_debug{};

protected:
    // ------------------------------
    // Class fields
    // ------------------------------

    QToolBar *m_toolBar{};
    DrawingWidget *m_drawingWidget{};
};


#endif //APP_TOOLBAR_H
