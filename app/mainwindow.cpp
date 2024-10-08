#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), m_ui(new Ui::MainWindow), m_toolBar(new ToolBar(this)) {
    m_ui->setupUi(this);
    m_toolBar->setupToolBar(m_ui->toolBar);

    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}


MainWindow::~MainWindow() {
    delete m_ui;
}
