#ifndef FILLSKIM_MC_H
#define FILLSKIM_MC_H

#include "../Utility/untuplizer_v09.h"

// * Input variables
Int_t     nLHE_in;
int      *lhePID_in;
float    *lhePx_in;
float    *lhePy_in;
float    *lhePz_in;
float    *lheE_in;
Int_t     nMC_in;
int      *mcPID_in;
float    *mcPt_in;
float    *mcMass_in;
float    *mcEta_in;
float    *mcPhi_in;
float    *mcE_in;
Short_t  *mcStatusFlag_in;

// * Output variables
Int_t            nLHE_out;
vector<int>      lhePID_out;
vector<float>    lhePx_out;
vector<float>    lhePy_out;
vector<float>    lhePz_out;
vector<float>    lheE_out;
Int_t            nMC_out;
vector<int>      mcPID_out;
vector<float>    mcPt_out;
vector<float>    mcMass_out;
vector<float>    mcEta_out;
vector<float>    mcPhi_out;
vector<float>    mcE_out;
vector<Short_t>  mcStatusFlag_out;


// + Define branches
//------------------
void BranchSkim_MC (TTree *tree_output)
{
	tree_output -> Branch ("nLHE",         &nLHE_out);
	tree_output -> Branch ("lhePID",       &lhePID_out);
	tree_output -> Branch ("lhePx",        &lhePx_out);
	tree_output -> Branch ("lhePy",        &lhePy_out);
	tree_output -> Branch ("lhePz",        &lhePz_out);
	tree_output -> Branch ("lheE",         &lheE_out);
	tree_output -> Branch ("nMC",          &nMC_out);
	tree_output -> Branch ("mcPID",        &mcPID_out);
	tree_output -> Branch ("mcPt",         &mcPt_out);
	tree_output -> Branch ("mcMass",       &mcMass_out);
	tree_output -> Branch ("mcEta",        &mcEta_out);
	tree_output -> Branch ("mcPhi",        &mcPhi_out);
	tree_output -> Branch ("mcE",          &mcE_out);
	tree_output -> Branch ("mcStatusFlag", &mcStatusFlag_out);
}


// + Fill output
//--------------
void  FillSkim_MC (TreeReader &tree_input)
{
	// * Read variables form input
	nLHE_in         = tree_input . GetInt      ("nLHE");
	lhePID_in       = tree_input . GetPtrInt   ("lhePID");
	lhePx_in        = tree_input . GetPtrFloat ("lhePx");
	lhePy_in        = tree_input . GetPtrFloat ("lhePy");
	lhePz_in        = tree_input . GetPtrFloat ("lhePz");
	lheE_in         = tree_input . GetPtrFloat ("lheE");
	nMC_in          = tree_input . GetInt      ("nMC");
	mcPID_in        = tree_input . GetPtrInt   ("mcPID");
	mcPt_in         = tree_input . GetPtrFloat ("mcPt");
	mcMass_in       = tree_input . GetPtrFloat ("mcMass");
	mcEta_in        = tree_input . GetPtrFloat ("mcEta");
	mcPhi_in        = tree_input . GetPtrFloat ("mcPhi");
	mcE_in          = tree_input . GetPtrFloat ("mcE");
	mcStatusFlag_in = tree_input . GetPtrShort ("mcStatusFlag");

	// * Clean containers
	nLHE_out         = 0;
	lhePID_out       . clear();
	lhePx_out        . clear();
	lhePy_out        . clear();
	lhePz_out        . clear();
	lheE_out         . clear();
	nMC_out          = 0;
	mcPID_out        . clear();
	mcPt_out         . clear();
	mcMass_out       . clear();
	mcEta_out        . clear();
	mcPhi_out        . clear();
	mcE_out          . clear();
	mcStatusFlag_out . clear();

	// * Fill the containers
	nLHE_out = nLHE_in;

	for (int i=0; i<nLHE_out; i++)
	{
		lhePID_out . push_back (lhePID_in[i]);
		lhePx_out  . push_back (lhePx_in[i]);
		lhePy_out  . push_back (lhePy_in[i]);
		lhePz_out  . push_back (lhePz_in[i]);
		lheE_out   . push_back (lheE_in[i]);
	}

	nMC_out = nMC_in;

	for (int i=0; i<nMC_out; i++)
	{
		mcPID_out        . push_back (mcPID_in[i]);
		mcPt_out         . push_back (mcPt_in[i]);
		mcMass_out       . push_back (mcMass_in[i]);
		mcEta_out        . push_back (mcEta_in[i]);
		mcPhi_out        . push_back (mcPhi_in[i]);
		mcE_out          . push_back (mcE_in[i]);
		mcStatusFlag_out . push_back (mcStatusFlag_in[i]);
	}
}

#endif
