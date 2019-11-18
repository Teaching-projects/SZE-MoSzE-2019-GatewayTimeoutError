#ifndef ANCESTOR_H
#define ANCESTOR_H
#include <string>
#include <iostream>
using namespace std;
class directory;


class item{
protected:
    string name;
    directory* parent;
public:
    item(string,directory*);
    virtual ~item()=0;
    string getname();
    directory* getparent();
};

#endif // ANCESTOR_H
