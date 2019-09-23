#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

class directory
{
private:
    string name;
    directory* parent;
    list <directory*> subdirectories;
public:
    directory(string,directory*);
    ~directory();
    string getName() const;
    void print();
    void ls();
    void makefolder(string);
    list<directory *> getSubdirectories() const;
    directory *getParent() const;
};

#endif // DIRECTORY_H
