#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "ancestor.h"
#include "file.h"
#include <list>
#include <vector>

class directory : public ancestor
{
private:
    list<ancestor*> subdirectories;
    void segedrmrf();
public:
    directory(string name,directory*parent);
    ~directory() override;
    string getname() override;
    list<ancestor *> &getSubdirectories();
    directory* getparent() override;
    void ls();
    bool hasDirs();
    void makefolder(string);
    void touch(string);
    int rm(string);
    void rmrf(string);
    bool isDir() const;
    void echo(string content, string name);
};
#endif // DIRECTORY_H
