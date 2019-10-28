#include "file.h"

file::file(string name, directory* parent):ancestor(name,parent)
{

}

string file::getname()
{
    return this->name;
}

directory *file::getparent()
{
    return this->parent;
}

file::~file(){
    //delete parent;
}
