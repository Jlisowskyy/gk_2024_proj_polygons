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
#include "../include/Restrictions/EdgeBezierRestriction.h"

/* Point restrictions includes */
#include "../include/Restrictions/PointGContinuousRestriction.h"
#include "../include/Restrictions/PointC1ContinuousRestriction.h"
#include "../include/Restrictions/PointG1ContinuousRestriction.h"

std::unordered_map<std::string, EdgeRestriction *(*)(Edge *)> EdgeRestrictions{
    {"horizontal", [](Edge *edge) -> EdgeRestriction *{ return new EdgeHorizontalRestriction(edge); }},
    {"vertical", [](Edge *edge) -> EdgeRestriction *{ return new EdgeVerticalRestriction(edge); }},
    {"const_length", [](Edge *edge) -> EdgeRestriction *{ return new EdgeConstLengthRestriction(edge); }},
    {"bezier", [](Edge *edge) -> EdgeRestriction *{ return new EdgeBezierRestriction(edge); }}
};

std::unordered_map<std::string, PointRestriction *(*)(Point *)> PointRestrictions{
    {"c1_continuous", [](Point *point) -> PointRestriction *{ return new PointC1ContinuousRestriction(point); }},
    {"g1_continuous", [](Point *point) -> PointRestriction *{ return new PointG1ContinuousRestriction(point); }},
    {"g_continuous", [](Point *point) -> PointRestriction *{ return new PointGContinuousRestriction(point); }}
};
