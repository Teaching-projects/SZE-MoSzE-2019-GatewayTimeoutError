#include "filesystem.h"
#include <stdlib.h>
filesystem::filesystem()
{
    root=new directory("root",nullptr);
    currentdir=root;
    this->load("saved.txt");
}

filesystem::~filesystem()
{
    delete root;
}
int filesystem::mkdir(string n)
{
    for(auto i:currentdir->getSubdirectories()){
            if(i->getname()==n){
                cout<<"Ez a nev mar foglalt"<<endl;
                return 0;
            }
    }
    currentdir->makefolder(n);
    return 1;
}
int filesystem::touch(string filename){
    for(auto i:currentdir->getSubdirectories()){
        if(i->getname()==filename){
            cout<<"Ez a nev mar foglalt"<<endl;
            return 0;
        }
    }
    currentdir->touch(filename);
    return 1;
}
void filesystem::ls(){
    directory* tmp;
    tmp=currentdir;
    list<string> path;
    path.push_front(currentdir->getname());
    while(tmp->getparent()!=nullptr){
        path.push_front(tmp->getparent()->getname());
        tmp=tmp->getparent();
    }
    for(auto i:path){
        cout<<i;
        cout<<"/";
    }
    cout<<endl;
    for(auto i:currentdir->getSubdirectories()){
        cout<<"   "<<i->getname();
        cout<<endl;
    }
}

int filesystem::cd(string to){
    if(to==".."){
        currentdir=currentdir->getparent();
        return 1;
    }
    int tmp=0;
    for(auto& i:currentdir->getSubdirectories()){
        if(i->getname()==to){
        tmp+=1;
        directory* temp=dynamic_cast<directory*>(i);
        if(temp!=nullptr){
            currentdir=temp;
            return 1;
        }
        else{
            cout<<"File-ba nem lehet cd-zni"<<endl;
            return 0;
        }
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

void filesystem::save(string fname){
    ofstream myfile(fname);
    if(myfile.is_open()){
        myfile<<this->root;
    }
}
void filesystem::load(string fname){
    ifstream myfile(fname);
    string line;
    getline(myfile,line);
    if(myfile.is_open()){
        while(getline(myfile,line)){
            istringstream iss(line);
                char f;
                string path;
                if (!(iss >> f >> path)) { break; };
                iss>>f>>path;
                vector<string> pathh=this->split(path,'/');
                if(f=='f'){
                    currentdir=root;
                    for(unsigned int i=1;i<pathh.size()-1;i++){
                        if(this->cd(pathh[i])==0) {
                            this->mkdir(pathh[i]);
                            system("CLS");
                        }
                        this->cd(pathh[i]);
                        system("CLS");
                    }
                    this->touch(pathh[pathh.size()-1]);                }
                else if(f=='d'){
                    currentdir=root;
                    for(unsigned int i=1;i<pathh.size()-1;i++){
                        if(this->cd(pathh[i])==0) {
                            this->mkdir(pathh[i]);
                            system("CLS");
                        }
                        this->cd(pathh[i]);
                        system("CLS");
                    }
                    this->mkdir(pathh[pathh.size()-1]);
                }
        }
        currentdir=root;
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
               else{
                   this->cd(argument1);
               }
           }
           else if(command=="cd.."){
               if(currentdir==root){
                   cout<<"Rootbol nem lehet cd..-zni"<<endl;
               }
               else
                   currentdir=currentdir->getparent();
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
           else if(command=="exit"){
               this->save("saved.txt");
               cout<<"VISZLAT"<<endl;
               break;
           }
           else std::cout<<"Unknown command"<<std::endl;
    } while (command!="exit");
}
