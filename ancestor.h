#ifndef ANCESTOR_H
#define ANCESTOR_H
#include <string>
#include <iostream>
using namespace std;
class directory;


class ancestor
{
protected:
    string name;
    directory* parent;
public:
    ancestor(string,directory*);
    virtual ~ancestor()=0;
    virtual string getname()=0;
    virtual directory* getparent()=0;
};

#endif // ANCESTOR_H
