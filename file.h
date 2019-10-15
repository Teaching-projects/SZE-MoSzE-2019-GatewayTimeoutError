#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>

using namespace std;

class file
{
private:
    string content;
    string filename;
public:
    file(string);
    string getFilename() const;
};

#endif // FILE_H
