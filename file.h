#ifndef FILE_H
#define FILE_H
#include "item.h"

class file:public item
{
private:
    string content;
public:
    file(string,item*);
    file(string,item*,string);
    ~file() override;
    void setContent(string);
    string getContent() const;
};

#endif // FILE_H
