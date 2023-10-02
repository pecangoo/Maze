#ifndef WRITERTOFILE_H
#define WRITERTOFILE_H

#include "models.h"
#include <fstream>

class WriterToFile
{
public:
    WriterToFile();
    void start_write(model maze_scheme, std::string path);

};

#endif // WRITERTOFILE_H
