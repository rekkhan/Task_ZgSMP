#ifndef FILLSKIM_INFO_H
#define FILLSKIM_INFO_H

#include "../Utility/untuplizer.h"

// * Input&output variables
Int_t       run;
Long64_t    event;
Int_t       nVtx;
Int_t       nGoodVtx;
Bool_t      isPVGood;
float       vtx;
float       vty;
float       vtz;
float       rho;
float       rhoAll;
float       rhoCentral;
ULong64_t   HLT;


// + Define branches
//------------------
void BranchSkim_MET (TTree *treeput)
{
	treeput -> Branch ("run",         &run);
	treeput -> Branch ("event",       &event);
	treeput -> Branch ("nVtx",        &nVtx);
	treeput -> Branch ("nGoodVtx",    &nGoodVtx);
	treeput -> Branch ("isPVGood",    &isPVGood);
	treeput -> Branch ("vtx",         &vtx);
	treeput -> Branch ("vty",         &vty);
	treeput -> Branch ("vtz",         &vtz);
	treeput -> Branch ("rho",         &rho);
	treeput -> Branch ("rhoAll",      &rhoAll);
	treeput -> Branch ("rhoCentral",  &rhoCentral);
	treeput -> Branch ("HLT",         &HLT);
}


// + Fill output
//--------------
int  FillSkim_MET (TreeReader treeput,  int year)
{
	// * Read and write variables
	HLT = GetLong64 ("HLTEleMuX");

	bool passTrigger = (HLT>>5&1) || (HLT>>40&1) || (HLT>>15&1) || (HLT>>42&1)|| (HLT>>14&1) || (HLT>>41&1);
	if (year == 2017)   (HLT>>14&1) || (HLT>>40&1);
	else if (year == 2018)   (HLT>>15&1) || (HLT>>40&1);

	if (!passTrigger)
	{
		return 0;
	}

	run        = GetInt    ("run");
	event      = GetLong64 ("event");
	nVtx       = GetInt    ("nVtx");
	nGoodVtx   = GetInt    ("nGoodVtx");
	isPVGood   = GetBool   ("isPVGood");
	vtx        = GetFloat  ("vtx");
	vty        = GetFloat  ("vty");
	vtz        = GetFloat  ("vtz");
	rho        = GetFloat  ("rho");
	rhoAll     = GetFloat  ("rhoAll");
	rhoCentral = GetFloat  ("rhoCentral");

	return 1;
}

#endif
