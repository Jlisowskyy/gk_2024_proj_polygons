//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "Restrictions.h"
#include "PointRestriction.h"
#include "EdgeRestriction.h"
#include "../GraphicObjects/Point.h"
#include "../GraphicObjects/Edge.h"

/* Edge restrictions includes */
#include "EdgeHorizontalRestriction.h"

/* Point restrictions includes */

std::unordered_map<std::string, EdgeRestriction *(*)(Edge *)> EdgeRestrictions{
        {"horizontal", [](Edge *edge) -> EdgeRestriction * { return new EdgeHorizontalRestriction(edge); }}
};

std::unordered_map<std::string, PointRestriction *(*)(Point *)> PointRestrictions{};