#include "file.h"

file::file(string name, ancestor* parent):ancestor(name,parent)
{

}

string file::getname()
{
    return this->name;
}

ancestor *file::getparent()
{
    return this->parent;
}

file::~file(){
}

/*void file::Printfile(std::ostream& os,
                 file *d) const{
    list<string> path;
    ancestor* temp=d->getparent();
    os<<d->getparent()->getname();
    path.push_front(temp->getname());
    while(d->getparent()){
       path.push_front(d->getparent()->getname());
       temp=temp->getparent();
    }
    os<<"f ";
    for(auto i:path){
          os<<i<<"/";
        }
    os<<d->getname()<<endl;
}

std::ostream& operator << (std::ostream& os, file* d) {
  d->Printfile(os,d);
  return os;
}*/
