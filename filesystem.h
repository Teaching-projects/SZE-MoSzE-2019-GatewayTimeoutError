#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>

class filesystem
{
private:
    directory* root;
    directory* currentdir;
public:
    filesystem();
    ~filesystem();
    int mkdir(string);
    int touch(string);
    void ls();
    int cd(string);
    void start();
    int absoulutepathcd(string);
    vector<string> split(const string&, const char&);
};

#endif // FILESYSTEM_H
