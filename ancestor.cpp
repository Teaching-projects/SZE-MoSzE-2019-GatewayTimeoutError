#include "ancestor.h"

ancestor::ancestor(string name, ancestor* parent) : name(name), parent(parent){}

ancestor::~ancestor(){};
