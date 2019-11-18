#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "item.h"
#include "file.h"
#include <list>
#include <vector>

class directory : public item
{
private:
    list<item*> items;
    void segedrmrf();
public:
    directory(string name,directory*parent);
    ~directory() override;
    list<item *> getItems() const;
    void ls();
    bool hasDirs();
    void makefolder(string);
    void touch(string);
    void rm(string);
    void rmrf(string);
};
#endif // DIRECTORY_H
