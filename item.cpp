#include "item.h"

void item::setName(const string &value)
{
    name = value;
}

item::item(string name, item* parent)
{
    this->name=name;
    this->parent=parent;
}

string item::getname()
{
    return this->name;
}

item *item::getparent()
{
    return this->parent;
}

void item::setparent(item *p)
{
    this->parent=p;
}

item::~item(){};
