#ifndef ELLER_H
#define ELLER_H
#include "models.h"
#include <vector>

/*
 * @brief реализация алгоритма Эллера
 */
class Eller
{
public:
    Eller();
    void start_create_maze_eller(model *maze_model, int rows, int cols);


private:
    std::vector<int> maze_sets;
    void fill_empty_value_1(int cols);
    void assign_unique_set_2(int cols, int current_row);
    void create_random_borders_3_1(model *maze_model, int cols, int rows);

    void add_borders_3_1_1(model * maze_model, int cols, int current_row);
    void merge_sets_3_2(int current_row, int index, int element, int cols);

    void create_down_borders_4_1(model *maze_model, int cols, int rows);
    void copy_prev_in_next_row_5_1(model *maze_model, int cols, int current_row);
    void action_after_generate_5_2(model *maze_model, int cols, int current_row);
    void checkedEndLine(model *maze_model, int cols, int current_row);


    void addingVerticalWalls_3_1(model *maze_model, int cols, int current_row);
    void mergeSet_3_2(int index, int element, int cols);

    int counter;


};

#endif // ELLER_H
