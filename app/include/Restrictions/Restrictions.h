//
// Created by Jlisowskyy on 13/10/24.
//

#ifndef APP_RESTRICTIONS_H
#define APP_RESTRICTIONS_H

/* external includes */
#include <unordered_map>
#include <string>

/* Forward declarations */
class PointRestriction;

class EdgeRestriction;

class Edge;

class Point;

/* Edge restrictions */
extern std::unordered_map<std::string, EdgeRestriction *(*)(Edge *)> EdgeRestrictions;

/* Point restrictions */
extern std::unordered_map<std::string, PointRestriction *(*)(Point *)> PointRestrictions;

inline std::string EdgeRestrictionIconPath(const char *str) {
    return ":/icons/" + std::string(str) + "_edge_restriction_icon.png";
}

inline std::string PointIconRestrictionPath(const char *str) {
    return ":/icons/" + std::string(str) + "_point_restriction_icon.png";
}

#endif //APP_RESTRICTIONS_H
