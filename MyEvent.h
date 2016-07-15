#ifndef MyEvent_h
#define MyEvent_h

#include <vector>
#include <iostream>

#include "TObject.h"
#include "MyBaseObj.h"
#include "MyDerivObj.h"


class MyEvent : public TObject
{
public:

   MyEvent() : TObject(), mySet() {}

   void Generate()
   {
      for (int i=0; i!=10; i++) {
         mySet.push_back(new MyDerivObj());
      }
   }

   void Clear()
   {
      while (!mySet.empty()) delete *mySet.begin(), mySet.erase(mySet.begin());
   }

   virtual void Print(Option_t* option = "") const
   {
      std::cout << "my set: " << std::endl;
      for (const MyBaseObj* myEntry: mySet) {
         myEntry->Print();
         std::cout << std::endl;
      }
   }

protected:

   std::vector<MyBaseObj*> mySet;

   ClassDef(MyEvent, 1)
};

#endif
