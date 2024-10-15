//
// Created by Jlisowskyy on 10/10/24.
//

#ifndef APP_CONSTANTS_H
#define APP_CONSTANTS_H

#include <Qt>

/* Point specific */
static constexpr int DEFAULT_POINT_RADIUS = 7;
static constexpr int SELECTED_POINT_RADIUS = 10;

/* Selection specific */
static constexpr Qt::GlobalColor DEFAULT_COLOR = Qt::black;
static constexpr Qt::GlobalColor SELECTED_COLOR = Qt::darkRed;

/* Edge specific */
static constexpr int DEFAULT_EDGE_WIDTH = 5;
static constexpr int SELECTED_EDGE_WIDTH = 7;

/* Bezier specific */
static constexpr int BEZIER_CONTROL_POINT_RADIUS = 5;
static constexpr int BEZIER_HELP_LINE_WIDTH = 3;
static constexpr int BEZIER_LINE_LENGTH = 8;
static constexpr Qt::GlobalColor BEZIER_HELP_LINE_COLOR = Qt::darkBlue;

/* Connection specific */
enum ConnectionType : size_t {
    LEFT = 0,
    RIGHT = 1,
    NOT_CONNECTED = 2,
};
static constexpr size_t MAX_CONNECTIONS = NOT_CONNECTED;

constexpr size_t SwapDirection(const size_t direction) {
    return direction ^ 1;
}

/* Draw algorithm options */
enum LineDrawingAlgorithmType : size_t {
    DEFAULT = 0,
    BRESENHAM = 1,
};

extern bool BlockPropagation;

#endif //APP_CONSTANTS_H
