//
// Created by Jlisowskyy on 13/10/24.
//

/* internal includes */
#include "../include/Restrictions/Restrictions.h"
#include "../include/Restrictions/PointRestriction.h"
#include "../include/Restrictions/EdgeRestriction.h"
#include "../include/GraphicObjects/Point.h"
#include "../include/GraphicObjects/Edge.h"

/* Edge restrictions includes */
#include "../include/Restrictions/EdgeHorizontalRestriction.h"
#include "../include/Restrictions/EdgeVerticalRestriction.h"
#include "../include/Restrictions/EdgeConstLengthRestriction.h"

/* Point restrictions includes */

std::unordered_map<std::string, EdgeRestriction *(*)(Edge *)> EdgeRestrictions{
        {"horizontal", [](Edge *edge) -> EdgeRestriction * { return new EdgeHorizontalRestriction(edge); }},
        {"vertical", [](Edge *edge) -> EdgeRestriction * { return new EdgeVerticalRestriction(edge); }},
        {"const_length", [](Edge *edge) -> EdgeRestriction * { return new EdgeConstLengthRestriction(edge); }},
};

std::unordered_map<std::string, PointRestriction *(*)(Point *)> PointRestrictions{};