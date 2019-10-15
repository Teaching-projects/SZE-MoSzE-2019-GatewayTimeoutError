#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "directory.h"
#include <list>

class filesystem
{
private:
    list <directory*> directories;
    directory* root;
    list<string> path;
public:
    filesystem();
    ~filesystem();
    int mkdir(string);
    int touch(string);
    void ls();
    int cd(string);
    directory* currentdir;
    void start();
};

#endif // FILESYSTEM_H
