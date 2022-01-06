#ifndef FILLSKIM_EVENTGLOBAL_H
#define FILLSKIM_EVENTGLOBAL_H

#include "../Utility/untuplizer_v09.h"

// * Input&output variables
Int_t      run;
Long64_t   event;
Int_t      nVtx;
Bool_t     isPVGood;
float      vtx;
float      vty;
float      vtz;
float      rho;
Long64_t   HLT;
float      puTrue;
float      genWeight;

float     *ptrPUTrue;
float      genWei;
bool       passTrigger;


// + Define branches
//------------------
void BranchSkim_EventGlobal (TTree *tree_output)
{
	tree_output -> Branch ("run",       &run);
	tree_output -> Branch ("event",     &event);
	tree_output -> Branch ("nVtx",      &nVtx);
	tree_output -> Branch ("isPVGood",  &isPVGood);
	tree_output -> Branch ("vtx",       &vtx);
	tree_output -> Branch ("vty",       &vty);
	tree_output -> Branch ("vtz",       &vtz);
	tree_output -> Branch ("rho",       &rho);
	tree_output -> Branch ("HLT",       &HLT);
	tree_output -> Branch ("puTrue",    &puTrue);
	tree_output -> Branch ("genWeight", &genWeight);
}


// + Fill output
//--------------
void  FillSkim_EventGlobal (TreeReader &tree_input,  int year,  bool isMC)
{
	// * Read and write variables
	run      = tree_input . GetInt    ("run");
	event    = tree_input . GetLong64 ("event");
	nVtx     = tree_input . GetInt    ("nVtx");
	isPVGood = tree_input . GetBool   ("isPVGood");
	vtx      = tree_input . GetFloat  ("vtx");
	vty      = tree_input . GetFloat  ("vty");
	vtz      = tree_input . GetFloat  ("vtz");
	rho      = tree_input . GetFloat  ("rho");
	HLT      = tree_input . GetLong64 ("HLTEleMuX");

	puTrue  = 0.0;
	genWeight = 1.0;

	if (isMC)
	{
		genWei = tree_input . GetFloat ("genWeight");
		genWeight = (genWei>0) ? 1.0 : -1.0;

		ptrPUTrue = tree_input . GetPtrFloat ("puTrue");
		puTrue = ptrPUTrue[1];
	}

	return 1;
}

#endif
