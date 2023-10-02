#ifndef MODELS_H
#define MODELS_H
#include <vector>
#include <iostream>
constexpr int START = 1;
constexpr int FINISH = -1;
constexpr int NEXT_STEP = -2;

enum _type {
    MAZE,
    CAVE
};

enum way {
    NO,
    UP,
    RIGHT,
    DOWN,
    LEFT,
    NOWAY
};

typedef struct maze_cave {
    std::vector<bool> first;
    std::vector<bool> second;
    std::vector<bool> line_way;
    int size_col;
    int size_rows;
} model;


typedef struct line {
    float x_start, y_start, x_finish, y_finish;
} line_points;


typedef struct ball {
    bool is;
    int x_pos, y_pos;
    int radius_x, radius_y;
    int row, col;
} baloon;

#endif // MODELS_H
