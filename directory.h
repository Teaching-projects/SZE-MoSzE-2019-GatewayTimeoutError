#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "item.h"
#include "file.h"

class directory : public item
{
private:
    list<item*> FileSystemObjects;
public:
    directory(string name,directory*parent);
    ~directory() override;
    directory* getparent();
    void ls();
    bool hasDirs();
    void makefolder(string);
    void touch(string);
    const list<item *> &getFileSystemObjects();
    int rm(string);
    int rmrf(string);
    void echo(string content, string name);
};
#endif // DIRECTORY_H
