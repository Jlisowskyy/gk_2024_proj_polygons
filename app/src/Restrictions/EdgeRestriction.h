//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_EDGERESTRICTION_H
#define APP_EDGERESTRICTION_H

/* internal includes */
#include "ObjectRestriction.h"
#include "../Constants.h"

/* external includes */
#include <Qt>
#include <array>
#include <QPoint>

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
    // protected methods
    // ------------------------------
protected:

    void _gatherNeighborEdges(std::array<Edge *, MAX_CONNECTIONS> &array);

    void onRestrictionDelete() override;

    QPoint getIconPosition() override;

    // ------------------------------
    // Class fields
    // ------------------------------

    Edge *m_edge{};
};


#endif //APP_EDGERESTRICTION_H
