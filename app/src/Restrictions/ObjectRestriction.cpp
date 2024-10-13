//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "ObjectRestriction.h"
#include "RestrictionIcon.h"
#include "../GraphicObjects/DrawingWidget.h"

/* external includes */

void ObjectRestriction::removeRestriction() {
    m_restrictionIcon->scene()->removeItem(m_restrictionIcon);

    onRestrictionDelete();
}

void ObjectRestriction::addRestrictionIcon(DrawingWidget *drawingWidget) {
    QPoint point = getIconPosition();
    std::string name = getIconName();

    m_restrictionIcon = new RestrictionIcon(name, this);
    drawingWidget->scene()->addItem(m_restrictionIcon);

    m_restrictionIcon->setPos(point);
}

void ObjectRestriction::onReposition() {
    QPoint point = getIconPosition();
    m_restrictionIcon->setPos(point);
}
