#ifndef DIRECTORY_H
#define DIRECTORY_H
#include "item.h"
#include "file.h"

/*!
	Konyvtar osztaly, ami kepes mas konyvtarakat/fileokat 	tarolni, es sok funkcio vegrehajthato rajt.
*/


class directory : public item
{
private:
/*!
	Itemeket tarolo lista
*/
    list<item*> FileSystemObjects;
public:
/*!	
	Konstruktor
	\param name String tipusu, konyvtar neve
	\param parent directoryra mutato, konyvtar ose	
*/
    directory(string name,directory*parent);
    ~directory() override;
/*!
	\return directory szulojet adja vissza
*/
    directory* getparent();
/*!
	Directoryban levo fileokat/directorykat jeleniti meg
*/
    void ls();
/*!
	\return True ha van benne directory/file, false ha nincs
*/
    bool hasDirs();
/*!
	Directory letrehozasa
	\param n Letrehozando directory neve
*/
    void makefolder(string n);
/*!
	File letrehozasa
	\param name Letrehozando file neve
*/
    void touch(string name);
/*!
	\return Directorykat/fileokat tartalmazo lista
*/
    const list<item *> &getFileSystemObjects();
/*!
	\param todelete Torolni kivant file/directory neve
	\return 0 ha nem sikerult(nem letezo objektum), 1 ha minden zokkenomentesen ment
*/
    int rm(string todelete);
/*!
	\param todelete Torolni kivant file/directory neve
	\return 0 ha nem sikerult(nem letezo objektum), 1 ha minden zokkenomentesen ment
*/
    int rmrf(string todelete);
/*!	
	File letrehozasa, benne valamilyen tartalommal
	\param content tartalom, amit a fajlba szeretnenk irni
	\param name file neve amit letre akarunk hozni
*/
    void echo(string content, string name);
};
#endif // DIRECTORY_H
