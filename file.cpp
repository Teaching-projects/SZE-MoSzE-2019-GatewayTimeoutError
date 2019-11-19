#include "file.h"

string file::getContent() const
{
    return content;
}
file::file(string name, ancestor* parent):ancestor(name,parent)
{

}

file::file(string name, ancestor *, string content):ancestor(name,parent)
{
    this->content=content;
}

string file::getname()
{
    return this->name;
}

ancestor *file::getparent()
{
    return this->parent;
}

void file::setContent(string content){
    this->content=content;
}


file::~file(){
}

