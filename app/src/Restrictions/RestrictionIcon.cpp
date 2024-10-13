//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "RestrictionIcon.h"
#include "ObjectRestriction.h"

/* external includes */
#include <QPixmap>
#include <QPainter>

RestrictionIcon::RestrictionIcon(const std::string &str, ObjectRestriction *restriction) :
        QGraphicsPixmapItem(),
        m_restriction(restriction) {

    QPixmap pixmap(str.c_str());

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int width = pixmap.width();
    int height = pixmap.height();
    int diameter = std::min(width, height);
    QPoint center(width / 2, height / 2);

    QColor grayColor(128, 128, 128, 128);
    QBrush grayBrush(grayColor);

    painter.setBrush(grayBrush);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(center, diameter / 2, diameter / 2);

    painter.end();

    setPixmap(pixmap.scaled(48, 48, Qt::KeepAspectRatio));

    /* icons should be above points and edges */
    setZValue(2);
}

void RestrictionIcon::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    if (event->button() != Qt::LeftButton) {
        QGraphicsItem::mousePressEvent(event);
    }

    m_restriction->removeRestriction();
}


