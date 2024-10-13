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

#endif //APP_RESTRICTIONS_H
