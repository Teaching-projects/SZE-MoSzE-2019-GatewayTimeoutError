#include "item.h"

item::item(string name, directory* parent)
{
    this->name=name;
    this->parent=parent;
}

string item::getname()
{
    return this->name;
}

directory *item::getparent()
{
    return this->parent;
}
item::~item(){};
