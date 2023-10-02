#ifndef MIKKIMOUSE_H
#define MIKKIMOUSE_H
#include "models.h"
#include <stack>
#include <vector>
#include <iostream>
class MikkiMouse
{
public:
    MikkiMouse();
    std::vector<int> start_searching(model *maze, baloon start_ball, baloon finish_ball);
    void point_array_creation(model * maze, std::vector<line_points> * array_lines);
private:
    std::vector<int> result_way;
    std::pair<int, int> current_point;

    int find_way(model maze);

    int get_value_from_vector(std::vector<int> array, int col, int row){
         return array[col + row*col];
    }
    bool get_value_from_vector(std::vector<bool> array, int col, int row){
         return array[col + row*col];
    }
    void set_value_in_vector(int col, int row, int value) {
         result_way[col + row] = value;
    }
    bool check_border(std::vector<bool> array, int pos){
        // std::cout << "POS "<< pos << std::endl;
        return array[pos];
    }
   int is_side_free(model maze, int current_step);
   int find_way(model *maze);
   int line_way_pos(model * maze, int pos_temp, int pos_current);
   int track = 1;




};

#endif // MIKKIMOUSE_H
