#include "directory.h"
#include <iomanip>


directory::directory(string name, directory *parent):ancestor(name,parent)
{

}

directory::~directory()
{
    for(auto i:FileSystemObjects){
        delete i;
    }
}

list<ancestor *> directory::getFileSystemObjects() const
{
    return FileSystemObjects;
}

directory *directory::getparent()
{
    directory* temp=dynamic_cast<directory*>(this->parent);
    return temp;
}

string directory::getname()
{
    return this->name;
}

void directory::ls(){
    for(ancestor* i:FileSystemObjects){
        cout<<i->getname()<<endl;
    }
}

bool directory::hasDirs()
{
    if(this->getFileSystemObjects().empty()){
        return false;
    }
    return true;
}

void directory::makefolder(string n)
{
    FileSystemObjects.push_back(new directory(n,this));
}

void directory::touch(string name)
{
    FileSystemObjects.push_back(new file(name,this));
}

void directory::rm(string todelete)
{
    std::list<ancestor*>::iterator i = FileSystemObjects.begin();
    while (i != FileSystemObjects.end())
    {
        if((*i)->getname()==todelete){
            directory* temp=dynamic_cast<directory*>(*i);
            if(temp!=nullptr){
            //ha üres a mappa kitöröljük és továbbiterálunk
                if(!temp->hasDirs())
                    FileSystemObjects.erase(i++);
                //ha nem üres meghívjuk a segedrmrf-et ami rekurzívan bejárja az adott mappát
                else{
                    cout<<"Az adott mappa nem ures"<<endl;
                    ++i;
                }
            }
            else{
                FileSystemObjects.erase(i++);
            }
        }
        else
        {
            ++i;
        }
    }

}
void directory::segedrmrf(){
    for(auto it=FileSystemObjects.begin();it!=FileSystemObjects.end();)
    {
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp!=nullptr){
            //ha a mappa nem üres meghívjuk a segedrmrf-et az adott mappára
            if(temp->hasDirs()){
                temp->segedrmrf();
            }
            //ha üres a mappa töröljük
            else if(!temp->hasDirs()){
                it=this->FileSystemObjects.erase(it);
            }
            else{
                it++;
            }
        }
        //ha fájl akkor töröljük
        else{
            it=this->FileSystemObjects.erase(it);
        }
    }
}
void directory::rmrf(string todelete)
{
    std::list<ancestor*>::iterator i = FileSystemObjects.begin();
    while (i != FileSystemObjects.end())
    {
        if((*i)->getname()==todelete){
            directory* temp=dynamic_cast<directory*>(*i);
            if(temp!=nullptr){
            //ha üres a mappa kitöröljük és továbbiterálunk
                if(!temp->hasDirs())
                    FileSystemObjects.erase(i++);
                //ha nem üres meghívjuk a segedrmrf-et ami rekurzívan bejárja az adott mappát
                else{
                    temp->segedrmrf();
                }
            }
            else{
                FileSystemObjects.erase(i++);
            }
        }
        else
        {
            ++i;
        }
    }
}

