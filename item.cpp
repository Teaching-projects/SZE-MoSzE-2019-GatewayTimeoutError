#include "item.h"

item::item(string name, item* parent): name(name), parent(parent){}


string item::getname()
{
    return this->name;
}

item *item::getparent()
{
    return this->parent;
}
item::~item(){};
