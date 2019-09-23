#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "directory.h"
#include <list>

class filesystem
{
private:
    list <directory*> directories;
    directory* root;
public:
    filesystem();
    ~filesystem();
    int mkdir(string);
    void ls();
    int cd(string);
    directory* currentdir;
    void start();
};

#endif // FILESYSTEM_H
