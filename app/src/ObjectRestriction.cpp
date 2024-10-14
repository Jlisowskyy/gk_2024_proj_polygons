//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/ObjectRestriction.h"
#include "../include/Restrictions/RestrictionIcon.h"
#include "../include/GraphicObjects/DrawingWidget.h"

/* external includes */

void ObjectRestriction::removeRestriction() {
    /* Add Restriction Icon may be overloaded */
    if (m_restrictionIcon != nullptr) {
        m_restrictionIcon->scene()->removeItem(m_restrictionIcon);
    }

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
    /* Add Restriction Icon may be overloaded */
    if (m_restrictionIcon == nullptr) {
        return;
    }

    QPoint point = getIconPosition();
    m_restrictionIcon->setPos(point);
}
