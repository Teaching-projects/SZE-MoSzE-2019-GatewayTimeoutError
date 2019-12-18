#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "directory.h"
#include <sstream>
#include <fstream>

/*!
	File rendszer osztaly, ami az egesz rendszert kezeli
*/



class filesystem
{  
private:
    directory* root;
/*!
	Jelenlegi directoryra mutato
*/
    directory* currentdir;
/*!
	\param n Letrehozando directory neve
	\return 0 ha hasznalatban van ez a nev, 1 ha minden okes
*/
    int mkdir(string n);
/*!
	\param filename Letrehozando file neve
	\return 0 ha hasznalatban van ez a nev, 1 ha minden okes
*/
    int touch(string filename);
/*!
	Kilistazza a currentdir objektumait
*/
    void ls();
/*!
	Mappavaltas
	\param to Mappa ahova atszeretnenk lepni
	\return 0 ha nem sikerult 1 ha sikerult
*/
    int cd(string to);
/*!
	File letrehozasa
	\param content File tartalma
	\param fname File neve
	\return 0 ha mar letezik 1 ha meg nem
*/
    int echo(string content,string fname);
/*!
	Load fuggvenyhez segedfgv
	\param n letrehozando mappa neve
	\return 0-t ad vissza, ha van mar ilyen nevu objektum, 1-et ad vissza ha sikerult
*/
    int mkdirwoerrormessage(string n);
/*!
	Load fuggvenyhez segedfgv
	\param to mappa ahova atszeretnenk lepni
	\return 0-t ad vissza ha nincs ilyen nevu mappa, 1-et ha sikerult
*/
    int cdwoerrormessage(string to);
/*!
	Abszoluteleres cd
	\param path mappa eleresi utja ahova atszeretnenk lepni
	\return 0 ha nincs ilyen ut, nem sikerult vegigjarni, 1 ha sikerult oda lepni
*/
    int absolutepathcd(string path);
/*!
	Abszoluteleres rm
	\param path mappa/file eleresi utja amit torolni szeretnenk
	\return 0 ha nincs ilyen ut, nem sikerult vegigjarni, nem sikerult torolni, 1 ha sikerult oda lepni
*/
    int absolutepathrm(string path);
/*!
	Abszoluteleres rmrf
	\param path mappa eleresi utja amit forceolva torolni szeretnenk
	\return 0 ha nincs ilyen ut, nem sikerult vegigjarni 1 ha sikerult oda lepni es torolni
*/
    int absolutepathrmrf(string path);
/*!
	Abszoluteleres mkdir
	\param path mappa eleresi utja ahol letreakarjuk hozni a mappat
	\return 0 ha nincs ilyen ut, nem sikerult vegigjarni, letezik mar ilyen nevu mappa/file 1 ha sikerult oda lepni es mappat letrehozni
*/
    int absolutepathmkdir(string path);
/*!
	Pathot felszeletelo fuggveny
	\param line ami a path
	\param delim elvalaszto karakter ami alapjan felszeljuk a linet
	\return path szetvagasa '\' karakterek menten, es ezt egy vektorba adja vissza
*/

    vector<string> split(const string& line, const char& delim);
/*!
	Abszoluteleres redundancia elkerulese miatt hasznalt segedfuggveny
	\param path mappa eleresi
	\return 0 ha nincs ilyen ut, nem sikerult vegigjarni 1 ha letezik ez a path
*/
    int util(vector<string> path);
public:
/*!
	Parameter nelkuli konstruktor
*/
    filesystem();
    ~filesystem();
/*!
	Filesystem inicializalasa
*/
    void start();
/*!
	Filesystem kimentese
	\param fname File neve ahova menteni szeretnenk	
*/
    void save(string fname);
/*!
	Filesystem betoltese
	\param fname File neve ahonnan beszeretnenk tolteni a filesystemet	
*/
    void load(string fname);
    friend std::ostream& operator << (std::ostream& os, directory* d);
    void Print(std::ostream& os,directory* d) const;
    directory *getRoot() const;
};

#endif // FILESYSTEM_H
