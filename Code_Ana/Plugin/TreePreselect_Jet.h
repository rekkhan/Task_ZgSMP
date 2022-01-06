#ifndef TREEPRESELECT_JET_H
#define TREEPRESELECT_JET_H


#include "../Utility/untuplizer_v09.h"

// * Input variables
int     nJet_in;
float  *jetPt_in;
float  *jetRawPt_in;
float  *jetEta_in;
float  *jetPhi_in;
float  *jetEn_in;
float  *jetRawEn_in;
float  *jetChHFrac_in;
float  *jetNeuHFrac_in;
float  *jetChEMFrac_in;
float  *jetNeuEMFrac_in;
int    *jetNCharged_in;
int    *jetNNeutral_in;
float  *jetMuonFrac_in;
int    *jetPUFullID_in;
float  *jetJECUnc_in;
float  *jetP4Smear_in;
float  *jetP4SmearUp_in;
float  *jetP4SmearDo_in;

// * Output variables
int            nJet_out;
vector<float>  jetPt_out;
vector<float>  jetRawPt_out;
vector<float>  jetEta_out;
vector<float>  jetPhi_out;
vector<float>  jetEn_out;
vector<float>  jetRawEn_out;
vector<float>  jetJECUnc_out;
vector<float>  jetP4Smear_out;
vector<float>  jetP4SmearUp_out;
vector<float>  jetP4SmearDo_out;
vector<int>    jetPass_out;


// + Define branches
//------------------
void BranchPreselect_Jet (TTree *tree_output)
{
	tree_output -> Branch ("nJet",          &nJet_out);
	tree_output -> Branch ("jetPt",         &jetPt_out);
	tree_output -> Branch ("jetRawPt",      &jetRawPt_out);
	tree_output -> Branch ("jetEta",        &jetEta_out);
	tree_output -> Branch ("jetPhi",        &jetPhi_out);
	tree_output -> Branch ("jetEn",         &jetEn_out);
	tree_output -> Branch ("jetRawEn",      &jetRawEn_out);
	tree_output -> Branch ("jetJECUnc",     &jetJECUnc_out);
	tree_output -> Branch ("jetP4Smear",    &jetP4Smear_out);
	tree_output -> Branch ("jetP4SmearUp",  &jetP4SmearUp_out);
	tree_output -> Branch ("jetP4SmearDo",  &jetP4SmearDo_out);
	tree_output -> Branch ("jetPass",       &jetPass_out);
}


// + Fill output
//--------------
bool passJetID;
bool jetPass;
bool passChEMFrac;

int  FillPreselect_Jet (TreeReader &tree_input,  int year,  int reproc)
{
	// * Clean containers
	nJet_out         = 0;
	jetPt_out        . clear();
	jetRawPt_out     . clear();
	jetEta_out       . clear();
	jetPhi_out       . clear();
	jetEn_out        . clear();
	jetRawEn_out     . clear();
	jetJECUnc_out    . clear();
	jetP4Smear_out   . clear();
	jetP4SmearUp_out . clear();
	jetP4SmearDo_out . clear();
	jetPass_out      . clear();

	// * Read variables form input
	nJet_in         = tree_input . GetInt      ("nJet");
	jetPt_in        = tree_input . GetPtrFloat ("jetPt");
	jetRawPt_in     = tree_input . GetPtrFloat ("jetRawPt");
	jetEta_in       = tree_input . GetPtrFloat ("jetEta");
	jetPhi_in       = tree_input . GetPtrFloat ("jetPhi");
	jetEn_in        = tree_input . GetPtrFloat ("jetEn");
	jetRawEn_in     = tree_input . GetPtrFloat ("jetRawEn");
	jetChHFrac_in   = tree_input . GetPtrFloat ("jetChHFrac");
	jetNeuHFrac_in  = tree_input . GetPtrFloat ("jetNeuHFrac");
	jetChEMFrac_in  = tree_input . GetPtrFloat ("jetChEMFrac");
	jetNeuEMFrac_in = tree_input . GetPtrFloat ("jetNeuEMFrac");
	jetNCharged_in  = tree_input . GetPtrInt   ("jetNCharged");
	jetNNeutral_in  = tree_input . GetPtrInt   ("jetNNeutral");
	jetMuonFrac_in  = tree_input . GetPtrFloat ("jetMuonFrac");
	jetPUFullID_in  = tree_input . GetPtrInt   ("jetPUFullID");
	jetJECUnc_in    = tree_input . GetPtrFloat ("jetJECUnc");
	jetP4Smear_in   = tree_input . GetPtrFloat ("jetP4Smear");
	jetP4SmearUp_in = tree_input . GetPtrFloat ("jetP4SmearUp");
	jetP4SmearDo_in = tree_input . GetPtrFloat ("jetP4SmearDo");

	// * Fill the containers
	nJet_out = nJet_in;

	for (int i=0; i<nJet_out; i++)
	{
		passChEMFrac  = (reproc==1 && year==2016 && jetChEMFrac_in[i] < 0.90);
		passChEMFrac |= (jetChEMFrac_in[i] < 0.80);

		jetPass  = (jetNeuHFrac_in[i] < 0.90);
		jetPass &= (jetNeuEMFrac_in[i] < 0.90);
		jetPass &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jetPass &= (jetMuonFrac_in[i] < 0.80);
		jetPass &= (jetChHFrac_in[i] > 0);
		jetPass &= (jetNCharged_in[i] > 0);
		jetPass &= passChEMFrac;

		jetPass &= (abs(jetEta_in[i]) < 2.4);
		jetPass &= (jetPt_in[i] > 30);

		jetPt_out        . push_back (jetPt_in[i]);
		jetRawPt_out     . push_back (jetRawPt_in[i]);
		jetEta_out       . push_back (jetEta_in[i]);
		jetPhi_out       . push_back (jetPhi_in[i]);
		jetEn_out        . push_back (jetEn_in[i]);
		jetRawEn_out     . push_back (jetRawEn_in[i]);
		jetJECUnc_out    . push_back (jetJECUnc_in[i]);
		jetP4Smear_out   . push_back (jetP4Smear_in[i]);
		jetP4SmearUp_out . push_back (jetP4SmearUp_in[i]);
		jetP4SmearDo_out . push_back (jetP4SmearDo_in[i]);
		jetPass_out      . push_back (jetPass);
	}

	return 1;
}


#endif
