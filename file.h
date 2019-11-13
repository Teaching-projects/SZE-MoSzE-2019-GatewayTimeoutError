#ifndef FILE_H
#define FILE_H
#include "ancestor.h"

class file:public ancestor
{
private:
    string content;
public:
    file(string,ancestor*);
    ~file() override;
    string getname() override;
    ancestor* getparent() override;
};

#endif // FILE_H
