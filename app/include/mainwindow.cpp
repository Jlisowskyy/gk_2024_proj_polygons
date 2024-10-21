/* internal includes */
#include "mainwindow.h"
#include "./ui_mainwindow.h"

/* external includes */
#include <QFrame>
#include <QLabel>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          m_ui(new Ui::MainWindow),
          m_toolBar(new ToolBar(this)),
          m_drawingWidget(new DrawingWidget(this)),
          m_polygon(new Polygon(this)),
          m_label(new QLabel("Space coordinates: (0, 0)", this)) {
    m_ui->setupUi(this);
    m_drawingWidget->setupPainter(m_polygon, m_label);
    m_polygon->setupMgr(m_drawingWidget);
    m_toolBar->setupToolBar(m_ui->toolBar, m_polygon, m_drawingWidget);

    m_ui->verticalLayout->addWidget(m_drawingWidget);

    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::HLine);
    frame->setFrameShadow(QFrame::Sunken);
    frame->setLineWidth(3);
    frame->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    m_ui->verticalLayout->addWidget(frame);

    m_label->setAlignment(Qt::AlignRight);
    QFont font = m_label->font();
    font.setPointSize(12);
    m_label->setFont(font);
    m_ui->verticalLayout->addWidget(m_label);

    /* other connects */
    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    /* m_toolbar -> ??? connects */
    connect(m_toolBar->m_cleanSpaceAction, &QAction::triggered, m_polygon, &Polygon::clearItems);
    connect(m_toolBar->m_addVertexAction, &QAction::triggered, m_polygon, &Polygon::setIsAddingVertices);
    connect(m_toolBar->m_moveAction, &QAction::triggered, m_drawingWidget, &DrawingWidget::setMovingSpace);
    connect(m_toolBar->m_drawAlgorithmAction, &QAction::triggered, m_drawingWidget, &DrawingWidget::setUseBresenham);
    connect(m_toolBar->m_cutEdgeAction, &QAction::triggered, m_polygon, &Polygon::cutEdge);

    /* m_drawingWidget -> ??? connects */
    connect(m_drawingWidget, &DrawingWidget::selectedItemChanged, m_toolBar, &ToolBar::selectionChanged);

    /* m_polygon -> ??? connects */

}


MainWindow::~MainWindow() {
    delete m_ui;
}
