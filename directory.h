#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <iostream>
#include <string>
#include <list>
#include "file.h"
using namespace std;

class directory
{
private:
    string name;
    directory* parent;
    list <directory*> subdirectories;
    list <file*> files;
public:
    directory(string,directory*);
    ~directory();
    string getName() const;
    void print();
    void ls();
    void lsfiles();
    void makefolder(string);
    list<directory *> getSubdirectories();
    directory *getParent() const;
    bool hasDirs();
    void rm(string);
    void segedrmrf();
    void rmrf(string);
    void touch(string);
    list<file *> getFiles() const;
};

#endif // DIRECTORY_H
