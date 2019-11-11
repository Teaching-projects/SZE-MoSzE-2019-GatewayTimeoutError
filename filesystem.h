#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>

class filesystem
{
private:
    directory* root;
    directory* currentdir;
    int mkdir(string);
    int touch(string);
    void ls();
    int cd(string);
public:
    filesystem();
    ~filesystem();
    void start();
};

#endif // FILESYSTEM_H
