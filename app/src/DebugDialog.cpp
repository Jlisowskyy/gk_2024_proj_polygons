//
// Created by Jlisowskyy on 20/10/24.
//

#include "../include/GraphicObjects/DebugDialog.h"

VertexInputDialog::VertexInputDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Vertex Input");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Vertex ID input
    QHBoxLayout *idLayout = new QHBoxLayout();
    QLabel *idLabel = new QLabel("Vertex idx:", this);
    m_idxSpinBox = new QSpinBox(this);
    m_idxSpinBox->setRange(0, INT_MAX);
    idLayout->addWidget(idLabel);
    idLayout->addWidget(m_idxSpinBox);
    mainLayout->addLayout(idLayout);

    // Move by input
    QHBoxLayout *moveLayout = new QHBoxLayout();
    QLabel *moveLabel = new QLabel("Move by:", this);
    m_moveXSpinBox = new QDoubleSpinBox(this);
    m_moveYSpinBox = new QDoubleSpinBox(this);
    m_moveXSpinBox->setRange(-INT_MAX, INT_MAX);
    m_moveYSpinBox->setRange(-INT_MAX, INT_MAX);
    moveLayout->addWidget(moveLabel);
    moveLayout->addWidget(m_moveXSpinBox);
    moveLayout->addWidget(m_moveYSpinBox);
    mainLayout->addLayout(moveLayout);

    // OK and Cancel buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *okButton = new QPushButton("OK", this);
    QPushButton *cancelButton = new QPushButton("Cancel", this);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &VertexInputDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &VertexInputDialog::reject);
}
