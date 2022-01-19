#ifndef TREEPRESELECT_EVENTGLOBAL_H
#define TREEPRESELECT_EVENTGLOBAL_H


#include "../Utility/untuplizer_v09.h"
#include "../Utility/puweicalc.h"

using namespace std;

// * Input&output variables
Int_t      run;
Long64_t   event;
Int_t      nVtx;
Long64_t   HLT;
float      puTrue;
float      genWeight;
float      puWeight;


// + Define branches
//------------------
void BranchPreselect_EventGlobal (TTree *tree_output)
{
	tree_output -> Branch ("run",       &run);
	tree_output -> Branch ("event",     &event);
	tree_output -> Branch ("nVtx",      &nVtx);
	tree_output -> Branch ("HLT",       &HLT);
	tree_output -> Branch ("puTrue",    &puTrue);
	tree_output -> Branch ("genWeight", &genWeight);
	tree_output -> Branch ("puWeight",  &puWeight);
}


// + Fill output
//--------------
int  FillPreselect_EventGlobal (TreeReader &tree_input,  PUWeightCalculator &puCal,  int year,  bool isMC, int leptype)
{
	// * Read and write variables
	run       = tree_input . GetInt    ("run");
	event     = tree_input . GetLong64 ("event");
	nVtx      = tree_input . GetInt    ("nVtx");
	HLT       = tree_input . GetLong64 ("HLT");
	puTrue    = tree_input . GetFloat  ("puTrue");
	genWeight = tree_input . GetFloat  ("genWeight");

	bool passHLT;
	passHLT  = (leptype==1) ? ((HLT>>5&1 || HLT>>40&1) && year==2016) : ((HLT>>14&1 || HLT>>15&1) && year==2016);
	passHLT |= (leptype==1) ? (HLT>>40&1 && year==2017) : (HLT>>14&1 && year==2017);
	passHLT |= (leptype==1) ? (HLT>>40&1 && year==2018) : (HLT>>15&1 && year==2018);

	if (!passHLT)   return 0;

	puWeight = 1.0;

	if (isMC)
	{
		puWeight = (float)puCal . GetWeight (run, puTrue);
	}

	return 1;
}



#endif
