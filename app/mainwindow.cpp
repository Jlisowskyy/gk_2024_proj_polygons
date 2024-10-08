#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          m_ui(new Ui::MainWindow),
          m_toolBar(new ToolBar(this)),
          m_painter(new Painter(this)),
          m_objectMgr(new ObjectMgr(this)) {
    m_ui->setupUi(this);
    m_toolBar->setupToolBar(m_ui->toolBar);
    m_painter->setupPainter(m_objectMgr);
    m_objectMgr->setupMgr(m_painter);
    m_ui->horizontalLayout->addWidget(m_painter);

    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}


MainWindow::~MainWindow() {
    delete m_ui;
}
