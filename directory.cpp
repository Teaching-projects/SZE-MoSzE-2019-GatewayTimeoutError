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

list<ancestor *> &directory::getSubdirectories()
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
            //ha üres a mappa kitöröljük és továbbiterálunk
                if(!temp->hasDirs()){
                    subdirectories.erase(i++);
                    return 1;
                }
                else{
                    cout<<"Az adott mappa nem ures"<<endl;
                    return 0;
                }
            }
            else{
                subdirectories.erase(i++);
                return 1;
            }
        }
        else
        {
            ++i;
        }
    }
    return 0;
}

void directory::segedrmrf(){
    for(auto it=subdirectories.begin();it!=subdirectories.end();)
    {
        directory* temp=dynamic_cast<directory*>(*it);
        if(temp!=nullptr){
            //ha a mappa nem üres meghívjuk a segedrmrf-et az adott mappára
            if(temp->hasDirs()){
                temp->segedrmrf();
            }
            //ha üres a mappa töröljük
            else if(!temp->hasDirs()){
                cout<<(*it)->getname()<<" torolve"<<endl;
                it=this->subdirectories.erase(it);
            }
        }
        //ha fájl akkor töröljük
        else{
            cout<<(*it)->getname()<<" torolve"<<endl;
            it=this->subdirectories.erase(it);
        }
    }

}

void directory::rmrf(string todelete)
{
    std::list<ancestor*>::iterator i = subdirectories.begin();
    while (i != subdirectories.end())
    {
        if((*i)->getname()==todelete){
            directory* temp=dynamic_cast<directory*>(*i);
            if(temp!=nullptr){
            //ha üres a mappa kitöröljük és továbbiterálunk
                if(!temp->hasDirs()){
                    cout<<(*i)->getname()<<" torolve"<<endl;
                    subdirectories.erase(i++);
                }
                //ha nem üres meghívjuk a segedrmrf-et ami rekurzívan bejárja az adott mappát
                else{
                    temp->segedrmrf();
                }
            }
            else{
                cout<<(*i)->getname()<<" torolve"<<endl;
                subdirectories.erase(i++);
            }
        }
        else
        {
            ++i;
        }
    }
}
bool directory::isDir() const
{
    return true;
}

