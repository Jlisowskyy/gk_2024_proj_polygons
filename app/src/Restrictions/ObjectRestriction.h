//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_OBJECTRESTRICTION_H
#define APP_OBJECTRESTRICTION_H

class ObjectRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    ObjectRestriction() = default;
    virtual ~ObjectRestriction() = default;

    // ------------------------------
    // Abstract methods
    // ------------------------------

    virtual bool applyRestriction() = 0;



};

#endif //APP_OBJECTRESTRICTION_H
