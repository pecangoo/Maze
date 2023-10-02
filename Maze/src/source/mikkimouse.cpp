#include "mikkimouse.h"

#include <string>
#include <iostream>
/*
 * @brief Ищем путь между двумя точками
 */

MikkiMouse::MikkiMouse()
{

}


std::vector<int> MikkiMouse::start_searching(model *maze, baloon start_ball, baloon finish_ball) {

    // Заполняем массив расстояний нулями
    for (int i = 0; i < maze->size_col* maze->size_rows; i++) {
        result_way.push_back(0);
        maze->line_way.push_back(0);
    }



    // Отмечаем точку финиша
    this->set_value_in_vector(finish_ball.col, finish_ball.row * maze->size_col, FINISH);
    this->set_value_in_vector(start_ball.col, start_ball.row * maze->size_col, START);

    // Проверяем
    // testing tester;
    // tester.show_vector("Конечная точка поставлена", result_way,
    //                    maze->size_col, maze->size_rows);


    // Идем до тупика, или до финиша попутно закидывая в стак координаты точек с непройденными ходами
    // Если тупик, возвращаемся до крайне точки из стака.

    current_point.first = start_ball.col;
    current_point.second = start_ball.row;

    // // // Определяем следующую клетку и возращаем ее в current_point.
        // Когда нашел клетку для прохода(меньшую или 0) то текущая клетка "растет" на 1.
        // Если тупик, то "след" "растет" на 1. Повторяем алгоритм.
     int disizion = NO;
    while(1) {
       disizion = find_way(maze);

       switch(disizion) {
        case -1:
            break;
        case UP:
            current_point.second -= 1;
            break;
        case DOWN:
            current_point.second += 1;
            break;
        case LEFT:
            current_point.first -= 1;
            break;
        case RIGHT:
            current_point.first += 1;
            break;
         case NO:
            break;
        }

       if (disizion == -1) {
            break;
        }
       // После приводим к идеальной модели и возращаем массивом
    }

    return result_way;
}

int MikkiMouse::find_way(model *maze) {
    int pos_temp, pos_current;
    int disizion = NO;
    int track_of_cell = track;
    if (!(current_point.second == 0)) {
        if (!check_border(maze->second, current_point.second*maze->size_col + current_point.first - maze->size_col)) {
            // Границы верху нет.
            // Координата: current_point.second*maze->size_col + current_point.first - maze->size_col
            pos_temp = current_point.second*maze->size_col + current_point.first - maze->size_col;
            pos_current = current_point.second*maze->size_col + current_point.first;

            if (result_way[pos_temp] < track) {
                result_way[pos_current] = track;

                if (result_way[pos_temp] == FINISH) {
                    maze->line_way[pos_current] = 1;
                    maze->line_way[pos_temp] = 1;
                    result_way[pos_temp] = track;
                    return FINISH;
                }

                if (track_of_cell > result_way[pos_temp]){
                    track_of_cell = result_way[pos_temp];
                    disizion = UP;
                } else {
                    disizion = UP;
                }

                line_way_pos(maze, pos_temp,pos_current);

                if (result_way[pos_temp] == 0) {
                    return UP;
                }

            }
        }

    }

    // Смотрим вниз
    // // Если есть нижняя граница на текущей клетке, то низа нет
    if( !check_border(maze->second, current_point.second*maze->size_col +
                      current_point.first)) {
        // границы внизу нет
        pos_temp = current_point.second*maze->size_col +
                current_point.first + maze->size_col;
        pos_current =  current_point.second*maze->size_col +
                current_point.first;

        // Координата: current_point.second*maze->size_col + current_point.first

        if (result_way[pos_temp] < track) {
            result_way[pos_current] = track;

            if (result_way[pos_temp] == FINISH) {
                maze->line_way[pos_current] = 1;
                maze->line_way[pos_temp] = 1;
                result_way[pos_temp] = track;
                return FINISH;
            }

            if (track_of_cell > result_way[pos_temp]){
                track_of_cell = result_way[pos_temp];
                disizion = DOWN;
            }

            line_way_pos(maze, pos_temp,pos_current);

            if (result_way[pos_temp] == 0) {
                return DOWN;
            }

        }
    }

    // Смотрим влево.
    // // Если столбец 0, то влево нет.
    // // Если на клетке слева есть граница, то лева нет.
    if (!(current_point.first == 0)) {
        if ( !check_border(maze->first,
                           current_point.second*maze ->size_col +
                           current_point.first - 1)) {
            // Границы слева нет
            // Координата:
            pos_temp = current_point.second*maze->size_col + current_point.first - 1;
            pos_current = current_point.second*maze->size_col + current_point.first;

            if (result_way[pos_temp] < track) {
                result_way[pos_current] = track;

                if (result_way[pos_temp] == FINISH) {
                    maze->line_way[pos_current] = 1;
                    maze->line_way[pos_temp] = 1;
                     result_way[pos_temp] = track;
                    return FINISH;
                }

                if (track_of_cell > result_way[pos_temp]){
                    track_of_cell = result_way[pos_temp];
                    disizion = LEFT;
                }

                line_way_pos(maze, pos_temp, pos_current);

                if (result_way[pos_temp] == 0) {
                    return LEFT;
                }


            }
        }
    }

    // Смотрим вправо.
    // Если есть нижняя граница на текущей клетке, то низа нет.
    if ( !check_border(maze->first,
                       current_point.second*maze->size_col +
                       current_point.first)) {
        // Границы справа нет
        // Координата: current_point.second*maze->size_col + current_point.first + 1
        pos_temp = current_point.second*maze->size_col +
                current_point.first + 1;
        pos_current = current_point.second*maze->size_col +
                current_point.first;

        if (result_way[pos_temp] < track) {
            result_way[pos_current] = track;
            if (result_way[pos_temp] == FINISH) {
                maze->line_way[pos_current] = 1;
                maze->line_way[pos_temp] = 1;
                result_way[pos_temp] = track;
                return FINISH;
            }

            disizion = RIGHT;

            if (track_of_cell > result_way[pos_temp]){
                track_of_cell = result_way[pos_temp];
                disizion = RIGHT;
            }

            line_way_pos(maze, pos_temp,pos_current);

        }
    }
    if (disizion == NO) {
         track += 1;
         result_way[current_point.second*maze->size_col +
                 current_point.first] = track;
    }

    return disizion;
}


int MikkiMouse::line_way_pos(model *maze, int pos_temp, int pos_current) {
    if (result_way[pos_temp] == 0) {
        maze->line_way[pos_current] = 1;

    } else if(result_way[pos_temp] < result_way[pos_current]) {
        maze->line_way[pos_current] = 0;
    }

     return 0;
}


void MikkiMouse::point_array_creation(model * maze,
                                      std::vector<line_points> * array_lines) {

    array_lines->clear();

    float step_x  = 500.0/maze->size_col,
        step_y = 500.0/maze->size_rows,
        radius_x = 500.0/maze->size_col / 2.0,
        radius_y = 500.0/maze->size_rows / 2.0;

    int col = 0, row = 0;
    float pos_current = 0;

    auto it = maze->line_way.begin();
    for (; it != maze->line_way.end(); it++) {
        pos_current = row * maze->size_col + col;

      if(*it) {
          line_points point;
          point.x_start = 3 + (step_x*col) + radius_x;
          point.y_start = 3 + (step_y * row) +  radius_y;
          // Далее проверяем правую и нижнию клетку
          if (maze->first[pos_current] != 1) {// Если нет границы справа тогда логично проверить клетку справа
              if (maze->line_way[pos_current + 1]) {
                      point.x_finish = 3+(step_x*(col+1)) + radius_x;
                      point.y_finish = 3+(step_y *row) +  radius_y;
                      array_lines->push_back(point);
                     
            }
          }
          if (maze->second[pos_current] != 1) {// Если нет границы cнизу тогда логично проверить клетку справа

              if (maze->line_way[pos_current + maze->size_col]) {
                      point.x_finish = 3+(step_x*(col)) + radius_x;
                      point.y_finish = 3+(step_y *(row+1)) +  radius_y;
                      array_lines->push_back(point);
            }
          }
      }

      if (col+1 ==  maze->size_col) {
          col = 0;
          row++;
          continue;
      } else {
        col++;
      }
  }
}
