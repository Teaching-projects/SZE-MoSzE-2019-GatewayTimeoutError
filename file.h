#ifndef FILE_H
#define FILE_H
#include "ancestor.h"

class file:public ancestor
{
private:
    string content;
public:
    file(string,directory*);
    file(string,directory*,string);
    ~file() override;
    void setContent(string);
    string getContent() const;
    string getname() override;
    directory* getparent() override;
};

#endif // FILE_H
