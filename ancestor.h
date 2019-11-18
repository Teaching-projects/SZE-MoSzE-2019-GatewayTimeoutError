#ifndef ANCESTOR_H
#define ANCESTOR_H
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
using namespace std;


class ancestor
{
protected:
    string name;
    ancestor* parent;
public:
    ancestor(string,ancestor*);
    virtual ~ancestor()=0;
    virtual string getname()=0;
    virtual ancestor* getparent()=0;
};

#endif // ANCESTOR_H
