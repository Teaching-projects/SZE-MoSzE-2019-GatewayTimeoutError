#include "file.h"

string file::getFilename() const
{
    return filename;
}

file::file(string filename)
{
    this->filename=filename;
    this->content="";
}
