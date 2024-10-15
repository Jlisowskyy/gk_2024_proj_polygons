//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_OBJECTRESTRICTION_H
#define APP_OBJECTRESTRICTION_H

/* internal includes */

/* external includes */
#include <string>
#include <QPoint>

/* forward declarations */

class DrawingWidget;

class RestrictionIcon;

class ObjectRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    ObjectRestriction() = default;

    virtual ~ObjectRestriction() = default;

    // ------------------------------
    // class interaction
    // ------------------------------

    virtual void addRestrictionIcon(DrawingWidget *drawingWidget);

    void removeRestriction();

    virtual void onReposition();

    // ------------------------------
    // Abstract methods
    // ------------------------------
public:

    virtual bool applyRestriction() = 0;

    virtual bool isRestrictionPreserved() = 0;

    virtual QPointF tryToPreserveRestriction(size_t direction, QPointF dxdy) = 0;

protected:

    virtual void onRestrictionDelete() {}

    virtual QPointF getIconPosition() { return {0, 0}; }

    virtual std::string getIconName() { return ""; }

    // ------------------------------
    // Class fields
    // ------------------------------

    RestrictionIcon *m_restrictionIcon{};
};


#endif //APP_OBJECTRESTRICTION_H
