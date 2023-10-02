#include "writertofile.h"

WriterToFile::WriterToFile()
{

}


void WriterToFile::start_write(model maze_scheme, std::string path) {

    std::string str = "";
    //std::cout  << "ROWS COLS " << maze_scheme.size_col << " " << maze_scheme.size_rows << std::endl;
    str += std::to_string(maze_scheme.size_col)
            + " " +
            std::to_string(maze_scheme.size_rows) + "\n";


    auto it = maze_scheme.first.begin();
    int count = 0;
    for (;it != maze_scheme.first.end(); it++) {
       // std::cout << *it;
        str += std::to_string(*it);
        if (count < maze_scheme.size_col-1) {
            count++;
            str+=" ";
        } else {
            str+="\n";
            count = 0;
        }
    }
     str+="\n";

     it = maze_scheme.second.begin();
     count = 0;
     for (;it != maze_scheme.second.end(); it++) {
         str += std::to_string(*it);
         if (count < maze_scheme.size_col-1) {
             count++;
             str+=" ";
           //  std::cout << " ";
         } else {
             str+="\n";
            // std::cout << std::endl;
             count = 0;
         }
     }

    std::cout << str << std::endl;


           std::ofstream out;          // поток для записи
           out.open(path);      // открываем файл для записи
           if (out.is_open())
               out << str << std::endl;
           out.close();
}
