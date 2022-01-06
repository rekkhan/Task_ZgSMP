#ifndef FILLSKIM_MET_H
#define FILLSKIM_MET_H

#include "../Utility/untuplizer_v09.h"

// * Input variables
Int_t metFilters;
float pfMET;
float pfMETPhi;


// + Define branches
//------------------
void BranchSkim_MET (TTree *tree_output)
{
	tree_output -> Branch ("metFilters", &metFilters);
	tree_output -> Branch ("pfMET",      &pfMET);
	tree_output -> Branch ("pfMETPhi",   &pfMETPhi);
}


// + Fill output
//--------------
void  FillSkim_MET (TreeReader &tree_input,  bool isMC)
{
	// * Read variables form input
	metFilters = 0;
	if (!isMC)   metFilters = tree_input . GetInt   ("metFilters");
	pfMET      = tree_input . GetFloat ("pfMET");
	pfMETPhi   = tree_input . GetFloat ("pfMETPhi");
}

#endif
