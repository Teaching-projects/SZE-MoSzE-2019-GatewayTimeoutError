#include "filesystem.h"
#include <sstream>
filesystem::filesystem()
{
    root=new directory("root",nullptr);
    currentdir=root;
}
filesystem::~filesystem(){
    delete root;
}

int filesystem::mkdir(string n)
{
    if(currentdir->getSubdirectories().empty()){
                currentdir->makefolder(n);
                return 1;
        }
        for(auto i:currentdir->getSubdirectories()){
            if(i->getName()==n){
                cout<<"Ilyen mappa mar van"<<endl;
                return 0;
            }
        }
    currentdir->makefolder(n);
    return 1;
}
int filesystem::touch(string filename){
    for(auto i:currentdir->getSubdirectories()){
        if(i->getName()==filename){
            return 0;
        }
    }
    for(auto i:currentdir->getFiles()){
        if(i->getFilename()==filename){
            return 0;
        }
    }
    currentdir->touch(filename);
    return 1;
}
void filesystem::ls(){
    directory* tmp;
    tmp=currentdir;
    path.push_front(currentdir->getName());
    while(tmp->getParent()!=nullptr){
        path.push_front(tmp->getParent()->getName());
        tmp=tmp->getParent();
    }
    //currentdir->print();
    //cout<<"/"<<endl;
    for(auto i:path){
        cout<<i;
        cout<<"/";
    }
    cout<<endl;
    for(auto i:currentdir->getSubdirectories()){
        i->ls();
        cout<<endl;
    }
    currentdir->lsfiles();
    path.clear();
}
//cd mukodik
int filesystem::cd(string to){
    if(to==".."){
        currentdir=currentdir->getParent();
        return 1;
    }
    int tmp=0;
    for(auto& i:currentdir->getSubdirectories()){
        //i->print();
        if(i->getName()==to){
        tmp+=1;
        currentdir=i;
        return 1;
        }
    }
    if(tmp==0){
        cout<<"Az adott mappa nem letezik"<<endl;
    }
    return 0;
}

vector<string> filesystem::split(const string& str, const char& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + 1;
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int filesystem::absoulutepath(string path){
    currentdir=root;
    vector<string>route=this->split(path,'/');
    int flag=1;
    for(unsigned int i=1;i<route.size();i++){
        for(auto j:currentdir->getSubdirectories()){
            if(j->getName()==route[i]){
                currentdir=j;
                flag++;
            }
        }
    }
    if(flag==route.size()){
        return 1;
    }
    else{
        cout<<"Nincs ilyen eleresi utvonal"<<endl;
        return 0;
    }
}


void filesystem::start(){
    string command;
    string fullcommand;
    string argument1;
    string argument2;
    do{
       getline(cin,fullcommand);
       istringstream line(fullcommand);
       command=argument1="";
       line>>command;
       line>>argument1;

           if (command=="ls")
           {
              this->ls();
           }
           else if (command=="cd")
           {
               if(argument1=="") cout<<"Adjon meg egy mappanevet"<<endl;
               else if(argument1.find("/")!=string::npos){
                   this->absoulutepath(argument1);
               }
               else{
                   this->cd(argument1);
               }
           }
           else if(command=="cd.."){
               if(currentdir==root){
                   cout<<"Rootbol nem lehet cd..-zni"<<endl;
               }
               else
                   currentdir=currentdir->getParent();
           }
           else if (command=="mkdir")
           {
               if(argument1=="")
                   cout<<"A mappat el kell nevezni"<<endl;
               else
               {
                  this->mkdir(argument1);
               }
           }
           else if (command=="rm"){
               if(argument1=="")
                   cout<<"Adja meg a mappa nevet amit torolni akar"<<endl;
               else {
                   currentdir->rm(argument1);
               }
           }
           else if(command=="rm-rf"){
               if(argument1=="")
                   cout<<"Adja meg a mappa nevet amit torolni akar"<<endl;
               else {
                   currentdir->rmrf(argument1);
               }
           }
           else if(command=="touch"){
               if(argument1=="")
                   cout<<"Adja meg a fajl nevet amit letre akar hozni"<<endl;
               else {
                   this->touch(argument1);
               }
           }
           else std::cout<<"Unknown command"<<std::endl;
    } while (command!="quit");
}

