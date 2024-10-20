//
// Created by Jlisowskyy on 20/10/24.
//

#ifndef APP_DEBUGDIALOG_H
#define APP_DEBUGDIALOG_H

/* external includes */
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QPointF>

class VertexInputDialog : public QDialog
{
Q_OBJECT

public:
    explicit VertexInputDialog(QWidget *parent = nullptr);

    [[nodiscard]] int getVertexIdx() const
    {
        return m_idxSpinBox->value();
    }

    [[nodiscard]] QPointF getMoveBy() const
    {
        return QPointF(m_moveXSpinBox->value(), m_moveYSpinBox->value());
    }

private:
    QSpinBox *m_idxSpinBox;
    QDoubleSpinBox *m_moveXSpinBox;
    QDoubleSpinBox *m_moveYSpinBox;
};


#endif //APP_DEBUGDIALOG_H
