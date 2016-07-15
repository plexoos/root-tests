#include "TFile.h"
#include "TChain.h"

#include "MyEvent.h"


int main(int argc, char **argv)
{
   TChain* myTreeChain = new TChain("t", "My Test TTree");
   myTreeChain->AddFile("mytree.root");

   MyEvent* myEvent = new MyEvent();

   myTreeChain->SetBranchAddress("e.", &myEvent);

   const int nTreeEvents = myTreeChain->GetEntries();

   for (int iEvent = 1; iEvent <= nTreeEvents; iEvent++)
   {
		myEvent->Clear();
		myTreeChain->GetEntry(iEvent-1);
		myEvent->Print();
   }

   delete myEvent;
   delete myTreeChain;

   return EXIT_SUCCESS;
}
