#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/* External includes */
#include <QApplication>
#include <QMainWindow>
#include <QLabel>

/* Internal includes */
#include "ObjectMgr.h"
#include "ToolBar.h"
#include "Painter.h"

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
    Painter *m_painter;
    ObjectMgr *m_objectMgr;
    QLabel *m_label;
};
#endif // MAINWINDOW_H
