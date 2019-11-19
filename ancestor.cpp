#include "ancestor.h"

ancestor::ancestor(string name, ancestor* parent)
{
    this->name=name;
    this->parent=parent;
}
ancestor::~ancestor(){};
