#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* External includes */
#include <QApplication>
#include <QMainWindow>
#include <QLabel>

/* Internal includes */
#include "ManagingObjects/Polygon.h"
#include "ManagingObjects/ToolBar.h"
#include "GraphicObjects/DrawingWidget.h"

QT_BEGIN_NAMESPACE

namespace Ui {
    class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    // ------------------------------
    // Class creation
    // ------------------------------

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    // ------------------------------
    // Class private methods
    // ------------------------------

    // ------------------------------
    // Class fields
    // ------------------------------

private:
    Ui::MainWindow *m_ui;
    ToolBar *m_toolBar;
    DrawingWidget *m_drawingWidget;
    Polygon *m_polygon;
    QLabel *m_label;
};
#endif // MAINWINDOW_H
