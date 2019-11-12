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
}

list<ancestor *> directory::getSubdirectories() const
{
    return subdirectories;
}

directory *directory::getparent()
{
    return this->parent;
}

bool directory::isDir() const
{
    return true;
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
void directory::Print(std::ostream& os,
                 directory *d) const{
    list<string> path;
    if(d->getparent()==nullptr){
        os<<d->getname()<<endl;
    }
    for(auto& i:d->getSubdirectories()){
        path.clear();
        directory* temp=dynamic_cast<directory*>(i);
        if(i->isDir() && !temp->hasDirs()){
            directory* parent = i->getparent();
            path.push_front(i->getparent()->getname());
            while(parent->getparent()){
                path.push_front(parent->getparent()->getname());
                parent=parent->getparent();
            }
            os<<"d ";
            for(auto i:path){
                os<<i<<"/";
            }
            os<<i->getname()<<endl;
        }
        else if(i->isDir() && temp->hasDirs()){
            this->Print(os, temp);
        }
        else if(i->isDir()==false){
            directory* temp2=i->getparent();
            path.push_front(temp2->getname());
            while(temp2->getparent()){
                path.push_front(temp2->getparent()->getname());
                temp2=temp2->getparent();
            }
            os<<"f ";
            for(auto i:path){
                os<<i<<"/";
            }
            os<<i->getname()<<endl;
        }
    }
}

std::ostream& operator << (std::ostream& os, directory* d) {
  d->Print(os,d);
  return os;
}

