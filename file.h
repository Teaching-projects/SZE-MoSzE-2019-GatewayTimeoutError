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
    string getname() override;
    directory* getparent() override;
    void setContent(string);
    bool isDir() const;
    string getContent() const;
};

#endif // FILE_H
