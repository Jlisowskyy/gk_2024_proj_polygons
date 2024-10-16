
//
// Created by Jlisowskyy on 17/10/24.
//

#ifndef APP_LENGTHDIALOG_H
#define APP_LENGTHDIALOG_H

/* internal includes */

/* external includes */
#include <QDialog>
#include <QLineEdit>

class LengthDialog : public QDialog {
Q_OBJECT

    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit LengthDialog(QWidget *parent, qreal init);

    // ------------------------------
    // Class interaction
    // ------------------------------

    qreal getLength() const { return m_length; }

protected slots:

    void acceptInput();

    // ------------------------------
    // Class fields
    // ------------------------------
protected:

    qreal m_length;
    QLineEdit *m_lengthInput;
};


#endif //APP_LENGTHDIALOG_H
