#include "directory.h"
#include <iomanip>


directory::directory(string name, directory *parent):ancestor(name,parent)
{

}

directory::~directory()
{
    //delete parent;
    for(auto i:subdirectories){
        delete i;
    }
}

list<ancestor *> directory::getSubdirectories() const
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

void directory::rm(string todelete)
{
    for(auto it=subdirectories.begin();it!=subdirectories.end();){
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp->getname()==todelete &&!temp->hasDirs()){
            it=this->subdirectories.erase(it);
        }
        else if(temp->getname()==todelete &&temp->hasDirs()){
            cout<<"Az adott mappa nem ures"<<endl;
            it++;
        }
        else{
            it++;
        }
    }

}
void directory::segedrmrf(){
    for(auto it=subdirectories.begin();it!=subdirectories.end();)
    {
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp!=nullptr){
            if(temp->hasDirs()){
                temp->segedrmrf();
            }
            else if(!temp->hasDirs()){
                it=this->subdirectories.erase(it);
            }
            else{
                it++;
            }
        }
        else{
            it=this->subdirectories.erase(it);
        }
    }
}
void directory::rmrf(string todelete)
{
    for(auto it=subdirectories.begin();it!=subdirectories.end();){
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp!=nullptr){
            if(temp->getname()==todelete &&!temp->hasDirs()){
                it=this->subdirectories.erase(it);
            }
            else if(temp->getname()==todelete &&temp->hasDirs()){
                temp->segedrmrf();
            }
            else{
                it++;
            }
        }
    }

}

