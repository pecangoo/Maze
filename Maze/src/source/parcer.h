#ifndef PARCER_H
#define PARCER_H
#include <vector>
#include <models.h>

class Parcer
{
public:
    Parcer();
    int start_parcer(model &final_model, std::string path);
    int size;
private:
    std::vector<int> split_line(std::string line);

};

#endif // PARCER_H
