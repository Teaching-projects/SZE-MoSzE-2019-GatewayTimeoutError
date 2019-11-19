#include "filesystem.h"

filesystem::filesystem()
{
    root=new directory("root",nullptr);
    currentdir=root;
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
        if(i->isDir()==false){
            file* temp=dynamic_cast<file*>(i);
            if(!temp->getContent().empty()){
            cout<<" ("<<temp->getContent()<<")";
            }
        }
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
        //i->print();
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

int filesystem::echo(string content,string fname){
    for(auto &i:currentdir->getSubdirectories()){
            if(i->getname()==fname){
                file* tempfile=dynamic_cast<file*>(i);
                if(tempfile){
                    tempfile->setContent(content);
                    return 1;
                }
                else{
                    cout<<"Directoryba nem lehet echozni"<<endl;
                    return 0;
                }
            }

    }
    currentdir->echo(content,fname);
    return 1;
}


void filesystem::start(){
    string command;
    string fullcommand;
    string argument1;
    string argument2;
    do{
       getline(cin,fullcommand);
       istringstream line(fullcommand);
       command=argument1=argument2="";
       line>>command;
       line>>argument1;
       line>>argument2;

           if (command=="ls")
           {
              this->ls();
           }
           else if (command=="cd")
           {
               if(argument1=="") cout<<"Adjon meg egy mappanevet"<<endl;
               else if(argument1==".."){
                   if(currentdir->getparent()!=nullptr) currentdir=currentdir->getparent();
                   else cout<<"cd .. nem megengedett a rootbol"<<endl;
               }
               else{
                   this->cd(argument1);
               }
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
               else if(argument1=="-rf"){
                   if(argument2==""){
                        cout<<"Adja meg a mappa nevet amit torolni akar"<<endl;
                   }
                   else {
                        currentdir->rmrf(argument2);
                    }
               }
               else {
                   currentdir->rm(argument1);
               }
           }
           else if(command=="touch"){
               if(argument1=="")
                   cout<<"Adja meg a fajl nevet amit letre akar hozni"<<endl;
               else {
                   this->touch(argument1);
               }
           }
           else if(command=="echo"){
               string content="";
               string arg="";
               int pos=fullcommand.find('"');
                if(pos!=std::string::npos && pos==5){
                    int pos2=fullcommand.find('"',pos+1);
                    if(pos2!=std::string::npos){
                        content=fullcommand.substr(pos+1,pos2-pos-1);
                        arg=fullcommand.substr(pos2+1);
                        istringstream args(arg);
                        char t;
                        string filenev;
                        args>>t;
                        args>>filenev;
                        if(t!='>' || filenev==""){
                            cout<<"Lemaradt valami"<<endl;
                        }
                        else if(t=='>' && filenev!=""){
                            echo(content,filenev);
                        }
                        }
                else{
                    cout<<"Unknown command"<<endl;
                }
               }
               else{
                   cout<<"Unknown command"<<endl;
               }
           }
           else if(command=="exit"){
               cout<<"VISZLAT"<<endl;
               break;
           }
           else std::cout<<"Unknown command"<<std::endl;
    } while (command!="exit");
}
