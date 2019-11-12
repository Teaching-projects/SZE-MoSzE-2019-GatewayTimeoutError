#include "ancestor.h"

ancestor::ancestor(string name, directory* parent)
{
    this->name=name;
    this->parent=parent;
}
ancestor::~ancestor(){};
