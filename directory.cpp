#include "directory.h"

string directory::getName() const
{
    return name;
}

void directory::print()
{
    cout<<this->getName()<<"/";
}

void directory::ls()
{
  this->print();
    /*for(auto& i:subdirectories){
        i->print();
    }*/
}

void directory::makefolder(string n)
{
    subdirectories.push_back(new directory(n,this));
}

list<directory *> directory::getSubdirectories()
{
    return subdirectories;
}

directory *directory::getParent() const
{
    return parent;
}

bool directory::hasDirs()
{
    if(this->getSubdirectories().empty()){
        return false;
    }
    return true;
}

void directory::rm(string todelete)
{
    for(auto it=subdirectories.begin();it!=subdirectories.end();){
        if((*it)->getName()==todelete &&!(*it)->hasDirs()){
            it=this->subdirectories.erase(it);
        }
        else if((*it)->getName()==todelete &&(*it)->hasDirs()){
            cout<<"Az adott mappa nem ures"<<endl;
            it++;
        }
        else{
            it++;
        }
    }

}
void directory::segedrmrf(){
    for(auto it=subdirectories.begin();it!=subdirectories.end();){
        if((*it)->hasDirs()){
            (*it)->segedrmrf();
        }
        else if(!(*it)->hasDirs()){
            it=this->subdirectories.erase(it);
        }
        else{
            it++;
        }
    }
}
void directory::rmrf(string todelete)
{
    for(auto it=subdirectories.begin();it!=subdirectories.end();){
        if((*it)->getName()==todelete &&!(*it)->hasDirs()){
            it=this->subdirectories.erase(it);
        }
        else if((*it)->getName()==todelete &&(*it)->hasDirs()){
            (*it)->segedrmrf();
        }
        else{
            it++;
        }
    }

}
directory::directory(string n, directory*parent)
{
    this->name=n;
    this->parent=parent;
}

directory::~directory()
{
        for(auto& i : subdirectories){
            delete i;
        }
}
