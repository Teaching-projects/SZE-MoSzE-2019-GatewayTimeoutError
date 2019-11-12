#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>
#include <fstream>

class filesystem
{
private:
    directory* root;
    directory* currentdir;
    int mkdir(string);
    int touch(string);
    void ls();
    int cd(string);
    vector<string> split(const string&, const char&);
    void save(string);
    void load(string);
public:
    filesystem();
    ~filesystem();
    void start();
};

#endif // FILESYSTEM_H
