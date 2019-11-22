#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>
#include <fstream>

class filesystem
{  
private:
    directory* root;
    directory* currentdir;
    int mkdir(string);
    int touch(string);
    void ls();
    int cd(string);
    int echo(string,string);
    int mkdirwoerrormessage(string);
    int cdwoerrormessage(string);
    int absolutepathcd(string);
    int absolutepathrm(string);
    int absolutepathrmrf(string);
    int absolutepathmkdir(string);
    vector<string> split(const string&, const char&);
    int util(vector<string>);
public:
    filesystem();
    ~filesystem();
    void start();
    void save(string);
    void load(string);
    friend std::ostream& operator << (std::ostream& os, directory* d);
    void Print(std::ostream& os,directory* d) const;
    directory *getRoot() const;
};

#endif // FILESYSTEM_H
