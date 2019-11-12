#ifndef FILE_H
#define FILE_H
#include "ancestor.h"

class file:public ancestor
{
private:
    string content;
public:
    file(string,directory*);
    ~file() override;
    string getname() override;
    directory* getparent() override;
    bool isDir() const;
};

#endif // FILE_H
