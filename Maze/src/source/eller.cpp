#include "eller.h"
#include <cstdlib>
#include <ctime>


Eller::Eller()
{
    counter = 1;
}


/*
 * brief Старт генерации лабиринта
 */

void Eller::start_create_maze_eller(model *maze_model, int rows, int cols) {

    // На данном этапе maze должна быть пустая
    maze_model->first.clear();
    maze_model->second.clear();
    maze_model->size_col = cols;
    maze_model->size_rows = rows;
    // Выделяем память под ячейки трех массивов.

    for(int i = 0; i< rows*cols; i++){
        maze_model->first.push_back(0);
        maze_model->second.push_back(0);
        maze_sets.push_back(0);
    }

    std::string str_test;

    int current_row = 0;

     
        // 2. Заполняем первую строку ячейки множествами.

        while(1) {
            assign_unique_set_2(cols, current_row);

            create_random_borders_3_1(maze_model, cols, current_row);

            if (current_row  + 1 < rows) {
                create_down_borders_4_1(maze_model, cols, current_row);
            } else {
                break;
            }

            // Если новая строка, то
            // Копируем предыдущую строку в новую строку.
            //if (current_row  + 1 < rows) {
                copy_prev_in_next_row_5_1(maze_model, cols, current_row);
          
            current_row++;

       }



        checkedEndLine(maze_model, cols, current_row);




}
void Eller::fill_empty_value_1(int cols) {
    for (int i = 0; i < cols; i++) {
        maze_sets.push_back(0);

    }
}

void Eller::assign_unique_set_2(int cols, int current_row) {
    // Доступ к вектору лабиринта происходит по индексу.
    // В случае с первым заполнением, индекс будет от 0 до col.
    // Далее индекс нужно будет считать или может создать промежуточный массив?
    for (int i = 0; i <  cols + cols*current_row; i++) {
        if (maze_sets[i] == 0) {
            maze_sets[i] = counter;
            counter++;
        }
    }
}

bool rand_bool() {
    return std::rand()/((RAND_MAX + 1u)/2);
}

void Eller::create_random_borders_3_1(model *maze_model, int cols, int current_row) {
     int current_pos = 0 + cols*current_row;
    for (int i = current_pos; i < cols + (cols*current_row); i++) {
           /* Ставим стенку или нет */
           bool choise = rand_bool();
           /* Проверка условия для предотовращения зацикливания */
           if (choise == true || maze_sets[i] == maze_sets[i + 1]) {
               maze_model->first[i] = true;
           } else {
               /* Объединение ячеек в одно множество */
               merge_sets_3_2(current_row, i, maze_sets[i] , cols);
           }
       }
       /* Добавление правой стенки в последней ячейки */
       maze_model->first[cols + (cols*current_row) - 1] = true;
}

void Eller::merge_sets_3_2(int current_row, int index, int element, int cols) {
    int current_pos = 0 + cols*current_row;
     int mutableSet = maze_sets[index + 1];
         for (int j = current_pos; j < cols + (cols*current_row); j++) {
             /* Проверка ячеек на одно множество */
             if (maze_sets[j] == mutableSet) {
                 /* Объединение ячейки в множество */
                 maze_sets[j] = element;
             }
         }

}

void Eller::create_down_borders_4_1(model *maze_model, int cols, int current_row) {

    int current_pos = 0 + cols*current_row;
    for (int i = current_pos; i < (cols + cols*current_row) - 1; i++) {
        if (maze_sets[i] == maze_sets[i+1])
            maze_model->second[i] = rand_bool();
        else
            maze_model->second[i] = false;
    }

    if (maze_sets[(cols + cols*current_row)-1] == maze_sets[(cols + cols*current_row)-2]) {
        int i = (cols + cols*current_row) - 2;
        bool flag = false;
            while(i > cols * current_row) {
                if (maze_model->second[i] == 0) {
                    flag = true;
                    break;
                }
                if (maze_sets[(cols + cols*current_row)-1] == maze_sets[i])
                    break;
               i--;
            }

    if (flag)
        maze_model->second[cols + cols*current_row - 1] = rand_bool();
    else
        maze_model->second[cols + cols*current_row - 1] = 0;
    } else {
        maze_model->second[cols + cols*current_row] = 0;
   }


}

void Eller::copy_prev_in_next_row_5_1(model *maze_model, int cols, int current_row) {
    int current_index = 0 + cols*current_row;
    int next_row_current =  cols + cols*current_row;
    for (; current_index < 0 + cols* (1+current_row); current_index++) {
        if (maze_model->second[current_index] != 1)
            maze_sets[next_row_current] =  maze_sets[current_index];
        else
            maze_sets[next_row_current] = 0;
        next_row_current++;
    }
}

void Eller::action_after_generate_5_2(model *maze_model, int cols, int current_row) {
    int current_index = 0 + cols*(current_row) ;
    // Добавляем ко всем ячейкам нижнюю строку
    for (; current_index < 0 + cols*(current_row+1); current_index++) {
        maze_model->second[current_index] = 1;
    }

    // Удаляем границы если разные множества у клеток
    current_index = 0 + cols*(current_row);
    for (; current_index < 0 + cols*(current_row+1) - 1; current_index++) {
        if (maze_sets[current_index] != maze_sets[current_index+1])
                maze_model->first[current_index] = 0;
    }


}


void Eller::checkedEndLine(model *maze_model, int cols, int current_row) {
    int current_index = 0 + cols * (current_row) ;
    for (int i = current_index; i < (cols + cols*current_row) - 1; i++) {
        if (maze_sets[i] != maze_sets[i + 1]) {
            maze_model->first[i] = 0;
            merge_sets_3_2(current_row, i, maze_sets[i] , cols);
        }
        maze_model->second[i] = 1;
    }
    maze_model->second[cols*current_row + cols -1] = 1;


}


