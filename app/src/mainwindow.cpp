/* internal includes */
#include "mainwindow.h"
#include "./ui_mainwindow.h"

/* external includes */
#include <QFrame>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_toolBar(new ToolBar(this)),
      m_painter(new Painter(this)),
      m_objectMgr(new ObjectMgr(this)),
      m_label(new QLabel("Space coordinates: (0, 0)", this)) {
    m_ui->setupUi(this);
    m_toolBar->setupToolBar(m_ui->toolBar, m_painter, m_objectMgr);
    m_painter->setupPainter(m_objectMgr, m_label);
    m_objectMgr->setupMgr(m_painter);

    m_ui->verticalLayout->addWidget(m_painter);

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

    connect(m_ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}


MainWindow::~MainWindow() {
    delete m_ui;
}
