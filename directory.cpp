#include "directory.h"

string directory::getName() const
{
    return name;
}

void directory::print()
{
    cout<<this->getName()<<"/";
}

void directory::ls()
{
  this->print();
    /*for(auto& i:subdirectories){
        i->print();
    }*/
}

void directory::makefolder(string n)
{
    subdirectories.push_back(new directory(n,this));
}

list<directory *> directory::getSubdirectories() const
{
    return subdirectories;
}

directory *directory::getParent() const
{
    return parent;
}

directory::directory(string n, directory*parent)
{
    this->name=n;
    this->parent=parent;
}

directory::~directory()
{
        for(auto& i : subdirectories){
            delete i;
        }
}
