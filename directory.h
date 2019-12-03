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
    void torol(item*);
    void echo(string content, string name);
    void mv(item *d);
    bool contains(string);
};
#endif // DIRECTORY_H
