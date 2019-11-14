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
    list<ancestor *> getFileSystemObjects() const;
    directory* getparent() override;
    void ls();
    bool hasDirs();
    void makefolder(string);
    void segedrmrf();
    void touch(string);
    int rm(string);
    void rmrf(string);
};
#endif // DIRECTORY_H
