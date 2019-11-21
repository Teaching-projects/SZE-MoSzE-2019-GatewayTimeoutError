#include "directory.h"
#include <iomanip>



directory::directory(string name, directory *parent):item(name,parent)
{

}

directory::~directory()
{
    for(auto i:FileSystemObjects){
        delete i;
    }
}

const list<item *> &directory::getFileSystemObjects()
{
    return FileSystemObjects;
}

directory *directory::getparent()
{
    directory* temp=dynamic_cast<directory*>(this->parent);
    return temp;
}

void directory::ls(){
    for(item* i:FileSystemObjects){
        cout<<i->getname()<<endl;
    }
}

bool directory::hasDirs()
{
    return !this->getFileSystemObjects().empty();
}

void directory::makefolder(string n)
{
    FileSystemObjects.push_back(new directory(n,this));
}

void directory::touch(string name)
{
    FileSystemObjects.push_back(new file(name,this));
}

void directory::echo(string content, string name){
    FileSystemObjects.push_back(new file(name,this,content));
}


int directory::rm(string todelete)
{
    std::list<item*>::iterator i = FileSystemObjects.begin();
    while (i != FileSystemObjects.end())
    {
        if((*i)->getname()==todelete){
            directory* temp=dynamic_cast<directory*>(*i);
            if(temp!=nullptr){
                //ha üres a mappa kitöröljük
                if(!temp->hasDirs()){
                    cout<<(*i)->getname()<< " torolve"<<endl;
                    FileSystemObjects.erase(i);
                    return 1;
                }
                else{
                    cout<<"Az adott mappa nem ures"<<endl;
                    return 0;
                }
            }
            else{
                cout<<(*i)->getname()<< " torolve"<<endl;
                FileSystemObjects.erase(i);
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
    std::list<item*>::iterator i = FileSystemObjects.begin();
    while (i != FileSystemObjects.end())
    {
        if((*i)->getname()==todelete){
            cout<<(*i)->getname()<< " torolve"<<endl;
            FileSystemObjects.erase(i);
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
