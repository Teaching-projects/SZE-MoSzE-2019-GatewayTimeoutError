#include "directory.h"
#include <iomanip>


directory::directory(string name, directory *parent):ancestor(name,parent)
{

}

directory::~directory()
{
    for(auto i:subdirectories){
        delete i;
    }
    delete this;
}

const list<ancestor *> &directory::getSubdirectories()
{
    return subdirectories;
}

directory *directory::getparent()
{
    return this->parent;
}




string directory::getname()
{
    return this->name;
}

void directory::ls(){
    for(ancestor* i:subdirectories){
        cout<<i->getname()<<endl;
    }
}

bool directory::hasDirs()
{
    if(this->getSubdirectories().empty()){
        return false;
    }
    return true;
}

void directory::makefolder(string n)
{
    subdirectories.push_back(new directory(n,this));
}

void directory::touch(string name)
{
    subdirectories.push_back(new file(name,this));
}

void directory::echo(string content, string name){
    subdirectories.push_back(new file(name,this,content));
}


int directory::rm(string todelete)
{
    std::list<ancestor*>::iterator i = subdirectories.begin();
    while (i != subdirectories.end())
    {
        if((*i)->getname()==todelete){
            directory* temp=dynamic_cast<directory*>(*i);
            if(temp!=nullptr){
                //ha üres a mappa kitöröljük
                if(!temp->hasDirs()){
                    cout<<(*i)->getname()<< " torolve"<<endl;
                    subdirectories.erase(i);
                    return 1;
                }
                else{
                    cout<<"Az adott mappa nem ures"<<endl;
                    return 0;
                }
            }
            else{
                cout<<(*i)->getname()<< " torolve"<<endl;
                subdirectories.erase(i);
                return 1;
            }
        }
        else
        {
            ++i;
        }
    }
    cout<<"Nem letezo mappa/file"<<endl;
    return 0;
}

int directory::rmrf(string todelete)
{
    std::list<ancestor*>::iterator i = subdirectories.begin();
    while (i != subdirectories.end())
    {
        if((*i)->getname()==todelete){
            cout<<(*i)->getname()<< " torolve"<<endl;
            subdirectories.erase(i);
            return 1;
        }
        else
        {
            ++i;
        }
    }
    cout<<"Nem letezo mappa/file"<<endl;
    return 0;
}
bool directory::isDir() const
{
    return true;
}

