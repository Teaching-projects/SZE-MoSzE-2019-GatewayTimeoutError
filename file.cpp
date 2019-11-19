#include "file.h"

string file::getContent() const
{
    return content;
}

file::file(string name, directory* parent):ancestor(name,parent)
{

}

file::file(string name, directory *, string content):ancestor(name,parent)
{
    this->content=content;
}

string file::getname()
{
    return this->name;
}

directory *file::getparent()
{
    return this->parent;
}

void file::setContent(string content){
    this->content=content;
}

bool file::isDir() const
{
    return false;
}

file::~file(){
    delete this;
}
