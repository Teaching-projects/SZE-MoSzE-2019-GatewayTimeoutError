#ifndef FILE_H
#define FILE_H
#include "item.h"

class file:public item
{
public:
    file(string,directory*);
    ~file() override;
};

#endif // FILE_H
