#include <iostream>
#include <fstream>
#include "parcer.h"
Parcer::Parcer()
{

}

int Parcer::start_parcer(model &final_model, std::string path) {
    std::vector<int> line_vector;
    std::string line;

    int number_line = 0, number_bloc = 0;
       std::ifstream in(path); // окрываем файл для чтения
       if (in.is_open())
       {
           while (getline(in, line))
           {
                number_line++;
                line_vector = split_line(line);
               if (number_line == 1) { // В этом случаем проверяем полученный вектор. Должно быть два одинаковых числа.
                   // Проверяем строку на количество элементов. Матрицы двумерные, поэтому должно быть два элемента
                 if (line_vector.size() != 2)
                     return 1;

                 final_model.size_col = line_vector[0];
                 final_model.size_rows = line_vector[1];

               } else if (line == "") { // Тогда проверяем количество элементов в векторе. Они
                   number_bloc++;

//                   if (final_model._type == CAVE)
//                       break;

               } else {
                   // Если блок первый, то добавляем строку в первый вектор, иначе во второй
                   if (line_vector.size() != (long unsigned int)final_model.size_col)
                       return 1;

                   auto it = line_vector.begin();
                   for (;it != line_vector.end(); it++) {
                       if (number_bloc == 0) {
                        final_model.first.push_back(*it);
                       } else if (number_bloc == 1) {
                        final_model.second.push_back(*it);
                       }
                   }
           }
       }
       in.close();     // закрываем файл
    }
       return 0;
}


std::vector<int> Parcer::split_line(std::string line) {
    std::vector<int> result;
    std::string number;
    for (auto it = line.begin(); it != line.end(); it++) {
        if(*it == ' ' || *it == '\n') {
            result.push_back(atoi(number.c_str()));
            number = "";
        } else if (*it >= '0' && *it <= '9'){
            number += *it;
        }
   }
   result.push_back(atoi(number.c_str()));
   return result;
}

