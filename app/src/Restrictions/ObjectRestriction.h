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

    void addRestrictionIcon(DrawingWidget *drawingWidget);

    void removeRestriction();

    // ------------------------------
    // Abstract methods
    // ------------------------------
public:

    virtual bool applyRestriction() = 0;

protected:

    virtual void onRestrictionDelete() = 0;

    virtual QPoint getIconPosition() = 0;

    virtual std::string getIconName() = 0;

    // ------------------------------
    // Class fields
    // ------------------------------

    RestrictionIcon *m_restrictionIcon{};
};


#endif //APP_OBJECTRESTRICTION_H
