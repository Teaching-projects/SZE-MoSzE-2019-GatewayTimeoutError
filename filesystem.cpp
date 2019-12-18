#include "filesystem.h"
#include <stdlib.h>

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


int filesystem::mkdirwoerrormessage(string n)
{
    for(auto i:currentdir->getFileSystemObjects()){
            if(i->getname()==n){
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
        if(i->getparent()->getname()==currentdir->getname()){
        cout<<"   "<<i->getname();
        file* temp=dynamic_cast<file*>(i);
        if(temp!=nullptr){
            if(!temp->getContent().empty()){
            cout<<" ("<<temp->getContent()<<")";
            }
        }
        cout<<endl;
    }
    }
}

int filesystem::cd(string to){
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

vector<string> filesystem::split(const string& line, const char& delim)
{

    // Vector of string to save tokens
    vector <string> tokens;

    // stringstream class check1
    stringstream check1(line);

    string intermediate;

    // Tokenizing w.r.t. space ' '
    while(getline(check1, intermediate, delim))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

int filesystem::absolutepathcd(string path){
    currentdir=root;
    vector<string>route=this->split(path,'/');
    unsigned int flag=1;
    if(route[0]!="root"){
        cout<<"Nincs ilyen eleresi utvonal"<<endl;
        return 0;
    }
    for(unsigned int i=1;i<route.size();i++){
        for(auto j:currentdir->getFileSystemObjects()){
            directory* temp=dynamic_cast<directory*>(j);
            if(temp!=nullptr){
                if(temp->getname()==route[i]){
                    currentdir=temp;
                    flag++;
                }
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

int filesystem::absolutepathmkdir(string path){
    vector<string>route=this->split(path,'/');
    int n=route.size();
    string tocreate=route[n-1];
    int temp=this->util(route);
    if(temp==1){
        currentdir->makefolder(tocreate);
        return 1;
    }
    else{
        cout<<"Nincs ilyen eleresi utvonal"<<endl;
        return 0;
    }
}

int filesystem::absolutepathrm(string path)
{
    vector<string>route=this->split(path,'/');
    int n=route.size();
    string todelete=route[n-1];
    int temp=this->util(route);
    if(temp==1){
        currentdir->rm(todelete);
        return 1;
    }
    else{
        cout<<"Nincs ilyen eleresi utvonal"<<endl;
        return 0;
    }
}

int filesystem::absolutepathrmrf(string path)
{
    vector<string>route=this->split(path,'/');
    int n=route.size();
    string todelete=route[n-1];
    int temp=this->util(route);
    if(temp==1){
        currentdir->rmrf(todelete);
        return 1;
    }
    else{
        cout<<"Nincs ilyen eleresi utvonal"<<endl;
        return 0;
    }
}

int filesystem::util(vector<string> path){
    currentdir=root;
    unsigned int flag=1;
    if(path[0]!="root"){
        return 0;
    }
    for(unsigned int i=1;i<path.size()-1;i++){
        for(auto j:currentdir->getFileSystemObjects()){
            directory* temp=dynamic_cast<directory*>(j);
            if(temp!=nullptr){
                if(temp->getname()==path[i]){
                    currentdir=temp;
                    flag++;
                }
            }
        }
    }
    if(flag==path.size()-1){
        return 1;
    }
    return 0;
}

int filesystem::cdwoerrormessage(string to){
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
                return 0;
            }
            }
        }
        return 0;
}

int filesystem::echo(string content,string fname){
    for(auto &i:currentdir->getFileSystemObjects()){
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
                        if(this->cdwoerrormessage(pathh[i])==0) {
                            this->mkdirwoerrormessage(pathh[i]);
                        }
                        this->cdwoerrormessage(pathh[i]);
                    }
                    this->touch(pathh[pathh.size()-1]);                }
                else if(f=='d'){
                    currentdir=root;
                    for(unsigned int i=1;i<pathh.size()-1;i++){
                        if(this->cdwoerrormessage(pathh[i])==0) {
                            this->mkdirwoerrormessage(pathh[i]);
                        }
                        this->cdwoerrormessage(pathh[i]);
                    }
                    this->mkdirwoerrormessage(pathh[pathh.size()-1]);
                }
        }
        currentdir=root;
    }
}

int filesystem::move(string what, string to)
{
    item* temp;
    directory* temp2=currentdir;
    currentdir=root;
    if(what.find("/")!=string::npos){
        vector<string>route2=this->split(what,'/');
        if(route2[0]!="root"){
            cout<<"Nincs ilyen eleresi utvonal"<<endl;
            return 0;
        }
        for(unsigned int i=1;i<route2.size()-1;i++){
            for(auto j:currentdir->getFileSystemObjects()){
                directory* temp=dynamic_cast<directory*>(j);
                if(temp!=nullptr){
                    if(temp->getname()==route2[i]){
                        currentdir=temp;
                        break;
                    }
                }
            }
        }
        for(auto i:currentdir->getFileSystemObjects()){
            if(i->getname()==route2.back()){
                temp=i;
                break;
            }
        }

    }
    else{
    for(auto i:currentdir->getFileSystemObjects()){
        if(i->getname()==what){
            temp=i;
            break;
        }
    }
    }
    currentdir=root;
    vector<string>route=this->split(to,'/');
    unsigned int flag=1;
    if(route[0]!="root"){
        cout<<"Nincs ilyen eleresi utvonal"<<endl;
        return 0;
    }
    for(unsigned int i=1;i<route.size();i++){
        for(auto j:currentdir->getFileSystemObjects()){
            directory* temp=dynamic_cast<directory*>(j);
            if(temp!=nullptr){
                if(temp->getname()==route[i]){
                    currentdir=temp;
                    flag++;
                }
            }
        }
    }
    if(flag==route.size()){
        if(!currentdir->contains(route.back())){
            cout<<"Ilyen nevu mappa/file mar van abban a mappaban"<<endl;
            return 0;
        }
        temp->setparent(currentdir);
        currentdir->mv(temp);
        currentdir=temp2;
        return 1;
    }
    else if(flag==route.size()-1){
        string asd=route.back();
        if(!currentdir->contains(asd)){
            cout<<"Ilyen nevu mappa/file mar van abban a mappaban"<<endl;
            return 0;
        }
        temp->setparent(currentdir);
        temp->setName(asd);
        currentdir->mv(temp);
        currentdir=temp2;
        return 1;
    }
    else{
        cout<<"Az eleresi utvonal ahova masolni szeretne nem letezik"<<endl;
        return 0;
    }
}


void filesystem::start(){
    string save;
    string load;
    cout<<"Milyen fajlba mentsen: ";
    cin>>save;
    cout<<"Fajl ahonnan betoltson: ";
    cin>>load;
    cin.ignore();
    this->load(load);
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
               else if(argument1.find("/")!=string::npos){
                   this->absolutepathcd(argument1);
               }
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
               else if(argument1.find("/")!=string::npos){
                   this->absolutepathmkdir(argument1);
               }
               else
               {
                  this->mkdir(argument1);
               }
           }
           else if (command=="rm"){
                if(argument1=="")
                   cout<<"Adja meg a mappa nevet amit torolni akar"<<endl;
                else if(argument1.find("/")!=string::npos){
                    this->absolutepathrm(argument1);
                }
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
           }
           else if(command=="move"){
               this->move(argument1,argument2);
           }
           else if(command=="exit"){
               this->save(save);
               cout<<"VISZLAT"<<endl;
               break;
           }
           else std::cout<<"Unknown command"<<std::endl;
    } while (command!="exit");
}
