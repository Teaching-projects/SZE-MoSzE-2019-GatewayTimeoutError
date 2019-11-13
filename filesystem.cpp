#include "filesystem.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif


filesystem::filesystem()
{
    root=new directory("root",nullptr);
    currentdir=root;
}

filesystem::~filesystem()
{
    delete root;
}
directory *filesystem::getRoot() const
{
    return root;
}

int filesystem::mkdir(string n)
{
    for(auto i:currentdir->getFileSystemObjects()){
            if(i->getname()==n){
                cout<<"Ez a nev mar foglalt"<<endl;
                return 0;
            }
    }
    currentdir->makefolder(n);
    return 1;
}
int filesystem::touch(string filename){
    for(auto i:currentdir->getFileSystemObjects()){
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
    for(auto i:currentdir->getFileSystemObjects()){
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
    for(auto& i:currentdir->getFileSystemObjects()){
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

void filesystem::Print(std::ostream& os,
                 directory *d) const{
    list<string> path;
    for(auto& i:d->getFileSystemObjects()){
        path.clear();
        directory* temp=dynamic_cast<directory*>(i);
        //ha nem nullptr akkor directory
        //megnézzük, hogy van-e benne más mappa/fájl, ha nincs
        //kiírjuk a pathját a fájlba és elé írunk 1 d-t hogy directory
        if(temp!=nullptr && !temp->hasDirs()){
            directory* parent = dynamic_cast<directory*>(i->getparent());
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
        //ha van alkönyvtára/fájlja bejárjuk rekuzrzívan
        //és a végpontokat kiírjuk pathal együtt a print fgv segítségével
        else if(temp!=nullptr && temp->hasDirs()){
            this->Print(os, temp);
        }
        //ha nullptr akkor fájl, fájl elé f-et írunk
        //és kiírjuk a pathjával együtt
        else if(temp==nullptr){
            directory* temp2=dynamic_cast<directory*>(i->getparent());
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

std::ostream& operator << (std::ostream& os, filesystem* f) {
  f->Print(os,f->getRoot());
  return os;
}

void filesystem::save(string fname){
    ofstream myfile(fname);
    if(myfile.is_open()){
        myfile<<this;
    }
}
void filesystem::load(string fname){
    ifstream myfile(fname);
    string line;
    if(!myfile.is_open()){
        cout<<"Nem sikerult megnyitni"<<endl;
    }
    else if(myfile.is_open()){
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
                            system(CLEAR);
                        }
                        this->cd(pathh[i]);
                        system(CLEAR);
                    }
                    this->touch(pathh[pathh.size()-1]);                }
                else if(f=='d'){
                    currentdir=root;
                    for(unsigned int i=1;i<pathh.size()-1;i++){
                        if(this->cd(pathh[i])==0) {
                            this->mkdir(pathh[i]);
                            system(CLEAR);
                        }
                        this->cd(pathh[i]);
                        system(CLEAR);
                    }
                    this->mkdir(pathh[pathh.size()-1]);
                }
        }
        system(CLEAR);
        currentdir=root;
    }
}

void filesystem::start(){
    string save;
    string load;
    cout<<"Milyen fajlba mentsen: ";
    cin>>save;
    cout<<"Fajl ahonnan betoltson: ";
    cin>>load;
    this->load(load);
    string command;
    string fullcommand;
    string argument1;
    string argument2;
    do{
       cin.ignore();
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
               this->save(save);
               cout<<"VISZLAT"<<endl;
               break;
           }
           else std::cout<<"Unknown command"<<std::endl;
    } while (command!="exit");
}
