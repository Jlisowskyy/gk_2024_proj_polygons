//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_RESTRICTIONICON_H
#define APP_RESTRICTIONICON_H

/* external includes */

/* internal includes */
#include <QGraphicsPixmapItem>
#include <string>
#include <QGraphicsSceneMouseEvent>

/* forward declaration */
class ObjectRestriction;

class RestrictionIcon : public QGraphicsPixmapItem {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit RestrictionIcon(const std::string &str, ObjectRestriction *restriction);

    ~RestrictionIcon() override = default;

    // ------------------------------
    // Method overloads
    // ------------------------------
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    // ------------------------------
    // Class fields
    // ------------------------------

    ObjectRestriction *m_restriction{};
};


#endif //APP_RESTRICTIONICON_H
