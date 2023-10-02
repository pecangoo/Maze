#include "init_cave.h"
#include <random>

initCave::initCave()
{

}

void initCave::start_init(model * cave, int random_value){
    // Заполняем массив пещеры случайным образом.
    for (int i = 0; i < cave->size_col*cave->size_rows; i++) {
        cave->first.push_back(rand_solution(random_value));
    }

}

bool initCave::rand_solution(int random_value) {
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<int> dist(1, 100);
    for (int i = 0; i < 10; ++i) std::cout << dist(gen) << std::endl;
    int random_variable =  dist(gen);
    std::cout << "Rand variable " << random_variable << "Rand set: " << random_value << std::endl;
    if (random_variable > 0 && random_variable <= random_value)
        return 1;
    else
        return 0;
}
