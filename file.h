#ifndef FILE_H
#define FILE_H
#include "item.h"

/*!
	File osztaly
*/


class file:public item
{
private:
    string content;
public:
/*!
	Konstruktor
	\param name File neve
	\param parent File ose(ami egy directory lesz)
*/
    file(string name,item* parent);
/*!
	Konstruktor #2
	\param name File neve
	\param parent File ose(amie egy directory lesz)
	\param content File tartalma
*/
    file(string name,item* parent,string content);
    ~file() override;
/*!	
	File tartalmanak beallitasa
	\param content File tartalma
*/
    void setContent(string content);
/*!
	\return File tartalma stringben
*/
    string getContent() const;
};

#endif // FILE_H
