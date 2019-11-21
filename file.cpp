#include "file.h"

string file::getContent() const
{
    return content;
}
file::file(string name, item* parent):item(name,parent)
{

}

file::file(string name, item* parent, string content):item(name,parent)
{
    this->content=content;
}

void file::setContent(string content){
    this->content=content;
}


file::~file(){
}

