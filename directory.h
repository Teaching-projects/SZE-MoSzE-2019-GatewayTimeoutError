#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "ancestor.h"
#include "file.h"

class directory : public ancestor
{
private:
    list<ancestor*> FileSystemObjects;
public:
    directory(string name,directory*parent);
    ~directory() override;
    string getname() override;
    const list<ancestor *> &getFileSystemObjects();
    directory* getparent() override;
    void ls();
    bool hasDirs();
    void makefolder(string);
    int rm(string);
    int rmrf(string);
    void echo(string content, string name);
    void touch(string);
};
#endif // DIRECTORY_H
