//
// Created by Jlisowskyy on 17/10/24.
//

/* internal includes */
#include "../include/GraphicObjects/LengthDialog.h"

/* external includes */
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDoubleValidator>
#include <QMessageBox>

LengthDialog::LengthDialog(QWidget *parent, const qreal init) : QDialog(parent), m_length(init) {
    setWindowTitle("Set length");
    setFixedSize(200, 100);

    auto layout = new QVBoxLayout(this);

    auto lengthLabel = new QLabel("Length:", this);
    layout->addWidget(lengthLabel);

    auto lengthInput = new QLineEdit(this);
    layout->addWidget(lengthInput);

    auto okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &LengthDialog::acceptInput);
    lengthInput->setFocus();
    lengthInput->setValidator(new QDoubleValidator(1, 9999.99, 2, this));
    lengthInput->setText(QString::number(init));

    m_lengthInput = lengthInput;
}

void LengthDialog::acceptInput() {
    bool isSuccess;
    qreal length = m_lengthInput->text().toDouble(&isSuccess);

    if (isSuccess) {
        m_length = length;
        accept();
    } else {
        QMessageBox::warning(this, "Error", "Invalid input");
    };
}
