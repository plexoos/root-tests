#ifndef MyBaseObj_h
#define MyBaseObj_h

#include <cstdlib>
#include <iostream>

#include "TObject.h"


class MyBaseObj : public TObject
{
public:

   MyBaseObj() : TObject(), a(10+rand()%10), b(20+(rand()%10)/10.) {}

   virtual void Print(Option_t* option = "") const
   {
      std::cout << "\ta: " << a;
      std::cout << "\tb: " << b;
   }

protected:

   int    a;
   double b;

   ClassDef(MyBaseObj, 1)
};

#endif
