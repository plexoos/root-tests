#include <cstdlib>

#include "TFile.h"
#include "TTree.h"

#include "MyEvent.h"


int main(int argc, char **argv)
{
   std::srand(1);

   TFile outRootFile("mytree.root", "recreate", "My Test Tree", 1);

   TTree*   myTree = new TTree("t", "My Test TTree");
   MyEvent* myEvent = new MyEvent();

   myTree->Branch("e.", "MyEvent", &myEvent, 32000, 99);

   const int nTreeEvents = 5;

   for (int iEvent = 1; iEvent <= nTreeEvents; iEvent++)
   {
      myEvent->Generate();
      myTree->Fill();
      myEvent->Clear();
   }

   delete myEvent;

   outRootFile.Write();
   outRootFile.Close();

   return EXIT_SUCCESS;
}
