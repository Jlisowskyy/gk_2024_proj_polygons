//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_EDGERESTRICTION_H
#define APP_EDGERESTRICTION_H

/* internal includes */
#include "ObjectRestriction.h"

/* external includes */
#include <Qt>

/* Forward declaration */
class Edge;

class EdgeRestriction : public ObjectRestriction {
    // ------------------------------
    // Class creation
    // ------------------------------
public:

    explicit EdgeRestriction(Edge *edge) : m_edge(edge) {
        Q_ASSERT(edge != nullptr);
    };

    ~EdgeRestriction() override = default;

    // ------------------------------
    // Class fields
    // ------------------------------
protected:

    Edge *m_edge{};
};


#endif //APP_EDGERESTRICTION_H
