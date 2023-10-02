#ifndef INIT_CAVE_H
#define INIT_CAVE_H
#include "models.h"

class initCave
{
public:
    initCave();
    void start_init(model * cave, int random_value);

private:
    bool rand_solution(int random_value);

};

#endif // INIT_CAVE_H
