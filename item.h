#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <stdlib.h>
using namespace std;

/*!
  Absztrakt ososztaly a directory es file osztalynak
*/
class item{
protected:
    string name;
    item* parent;
public:
    item(string,item*);
    virtual ~item()=0;
/*!
	\return File/Directory nevet adja vissza.
*/
    string getname();
/*!
	\return File/Directory oset adja vissza.
*/
    item* getparent();
};

#endif // ITEM_H
