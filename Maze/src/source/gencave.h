#ifndef GENCAVE_H
#define GENCAVE_H
#include "models.h"

class genCave
{
public:
    genCave();
    void start_gen(model &cave, int steps, int Br, int Ds);

private:
   // int return_current(int row, int col, int size_col, int size_row);
    int return_current(int col, int row, int size_col, int size_row);

    int count_alive(model &cave, int col, int row);
};

#endif // GENCAVE_H
