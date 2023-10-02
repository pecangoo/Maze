#include "gencave.h"

genCave::genCave()
{

}


int genCave::return_current(int col, int row, int size_col, int size_row) {
    if (
            row < 0 ||
            col < 0 ||
            row == size_row ||
            col == size_col
        )
        return -1;
    return row*size_col + col;
};

int genCave::count_alive(model &cave, int col, int row) {
    int current_pos = 0,
         count_alive = 0;
    for (int c = - 1; c <= 1; c++) {
         for (int r = - 1; r <= 1; r++) {
             if (r == 0 && c == 0)
                 continue;
            current_pos = return_current(col+c, row+r, cave.size_col, cave.size_rows);
            if (current_pos != -1) {
                if (cave.first[current_pos] == 1)
                    count_alive++;
            }  else {
                count_alive++;
            }
         }
    }
    return count_alive;
}


void genCave::start_gen(model &cave, int steps, int Br, int Ds) {

    std::vector<bool> temp_cave = cave.first;
    int current = 0,
        value_alive = 0;
        for (int col = 0; col < cave.size_col; col++) {
            for (int row = 0; row < cave.size_rows; row++) {
                 value_alive = count_alive(cave, col, row);
                 current = return_current(col, row, cave.size_col, cave.size_rows);
                 if (cave.first[current] == 1) {
                     // Если жив, то должен умереть?
                     if (value_alive < Ds)
                        temp_cave[current] = 0;
                 } else {
                     // Если мертв, то должен возродиться?
                     if (value_alive > Br)
                        temp_cave[current] = 1;
                 }
            }
        }
        cave.first = temp_cave;
}
