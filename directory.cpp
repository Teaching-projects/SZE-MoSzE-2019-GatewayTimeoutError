#include "directory.h"
#include <iomanip>


directory::directory(string name, directory *parent):item(name,parent)
{

}

directory::~directory()
{
    //delete parent;
    for(auto i:items){
        delete i;
    }
}

list<item *> directory::getItems() const
{
    return items;
}

void directory::ls(){
    for(item* i:items){
        cout<<i->getname()<<endl;
    }
}

bool directory::hasDirs()
{
    if(this->getItems().empty()){
        return false;
    }
    return true;
}

void directory::makefolder(string n)
{
    items.push_back(new directory(n,this));
}

void directory::touch(string name)
{
    items.push_back(new file(name,this));
}

void directory::rm(string todelete)
{
    for(auto it=items.begin();it!=items.end();){
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp->getname()==todelete &&!temp->hasDirs()){
            it=this->items.erase(it);
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
    for(auto it=items.begin();it!=items.end();)
    {
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp!=nullptr){
            if(temp->hasDirs()){
                temp->segedrmrf();
            }
            else if(!temp->hasDirs()){
                it=this->items.erase(it);
            }
            else{
                it++;
            }
        }
        else{
            it=this->items.erase(it);
        }
    }
}
void directory::rmrf(string todelete)
{
    for(auto it=items.begin();it!=items.end();){
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp!=nullptr){
            if(temp->getname()==todelete &&!temp->hasDirs()){
                it=this->items.erase(it);
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

