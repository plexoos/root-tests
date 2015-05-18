#ifndef MyDerivObj_h
#define MyDerivObj_h

#include <cstdlib>
#include <iostream>

#include "TObject.h"


class MyDerivObj : public MyBaseObj
{
public:

   MyDerivObj() : MyBaseObj(), c(30+rand()%10) {}

   virtual void Print(Option_t* option = "") const
	{
		MyBaseObj::Print(option);
		std::cout << "\tc: " << c;
	}

protected:

   int c;

   ClassDef(MyDerivObj, 1)
};

#endif
