#ifndef ANCESTOR_H
#define ANCESTOR_H
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
using namespace std;

class item{
protected:
    string name;
    item* parent;
public:
    item(string,item*);
    virtual ~item()=0;
    string getname();
    item* getparent();
    void setparent(item *p);
    void setName(const string &value);
};

#endif // ANCESTOR_H
