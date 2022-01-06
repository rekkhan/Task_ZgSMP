#ifndef FILLSKIM_JET_H
#define FILLSKIM_JET_H

#include "../Utility/untuplizer_v09.h"

// * Input variables
Int_t   nJet_in;
float  *jetPt_in;
float  *jetRawPt_in;
float  *jetEta_in;
float  *jetPhi_in;
float  *jetEn_in;
float  *jetRawEn_in;
float  *jetCHF_in;
float  *jetNHF_in;
float  *jetCEF_in;
float  *jetNEF_in;
int    *jetNCH_in;
int    *jetNNP_in;
float  *jetMUF_in;
int    *jetPUFullID_in;
float  *jetJECUnc_in;
float  *jetP4Smear_in;
float  *jetP4SmearUp_in;
float  *jetP4SmearDo_in;

// * Output variables
Int_t          nJet_out;
vector<float>  jetPt_out;
vector<float>  jetRawPt_out;
vector<float>  jetEta_out;
vector<float>  jetPhi_out;
vector<float>  jetEn_out;
vector<float>  jetRawEn_out;
vector<float>  jetChHFrac_out;
vector<float>  jetNeuHFrac_out;
vector<float>  jetChEMFrac_out;
vector<float>  jetNeuEMFrac_out;
vector<int>    jetNCharged_out;
vector<int>    jetNNeutral_out;
vector<float>  jetMuonFrac_out;
vector<int>    jetPUFullID_out;
vector<float>  jetJECUnc_out;
vector<float>  jetP4Smear_out;
vector<float>  jetP4SmearUp_out;
vector<float>  jetP4SmearDo_out;

float  jetSmear;
float  jetSmearUp;
float  jetSmearDo;


// + Define branches
//------------------
void BranchSkim_Jet (TTree *tree_output)
{
	tree_output -> Branch ("nJet",          &nJet_out);
	tree_output -> Branch ("jetPt",         &jetPt_out);
	tree_output -> Branch ("jetRawPt",      &jetRawPt_out);
	tree_output -> Branch ("jetEta",        &jetEta_out);
	tree_output -> Branch ("jetPhi",        &jetPhi_out);
	tree_output -> Branch ("jetEn",         &jetEn_out);
	tree_output -> Branch ("jetRawEn",      &jetRawEn_out);
	tree_output -> Branch ("jetChHFrac",    &jetChHFrac_out);
	tree_output -> Branch ("jetNeuHFrac",   &jetNeuHFrac_out);
	tree_output -> Branch ("jetChEMFrac",   &jetChEMFrac_out);
	tree_output -> Branch ("jetNeuEMFrac",  &jetNeuEMFrac_out);
	tree_output -> Branch ("jetNCharged",   &jetNCharged_out);
	tree_output -> Branch ("jetNNeutral",   &jetNNeutral_out);
	tree_output -> Branch ("jetMuonFrac",   &jetMuonFrac_out);
	tree_output -> Branch ("jetPUFullID",   &jetPUFullID_out);
	tree_output -> Branch ("jetJECUnc",     &jetJECUnc_out);
	tree_output -> Branch ("jetP4Smear",    &jetP4Smear_out);
	tree_output -> Branch ("jetP4SmearUp",  &jetP4SmearUp_out);
	tree_output -> Branch ("jetP4SmearDo",  &jetP4SmearDo_out);
}


// + Fill output
//--------------
void  FillSkim_Jet (TreeReader &tree_input,  bool isMC)
{
	// * Clean containers
	nJet_out         = 0;
	jetPt_out        . clear();
	jetRawPt_out     . clear();
	jetEta_out       . clear();
	jetPhi_out       . clear();
	jetEn_out        . clear();
	jetRawEn_out     . clear();
	jetChHFrac_out   . clear();
	jetNeuHFrac_out  . clear();
	jetChEMFrac_out  . clear();
	jetNeuEMFrac_out . clear();
	jetNCharged_out  . clear();
	jetNNeutral_out  . clear();
	jetMuonFrac_out  . clear();
	jetPUFullID_out  . clear();
	jetJECUnc_out    . clear();
	jetP4Smear_out   . clear();
	jetP4SmearUp_out . clear();
	jetP4SmearDo_out . clear();

	// * Read variables form input
	nJet_in        = tree_input . GetInt      ("nJet");
	jetPt_in       = tree_input . GetPtrFloat ("jetPt");
	jetRawPt_in    = tree_input . GetPtrFloat ("jetRawPt");
	jetEta_in      = tree_input . GetPtrFloat ("jetEta");
	jetPhi_in      = tree_input . GetPtrFloat ("jetPhi");
	jetEn_in       = tree_input . GetPtrFloat ("jetEn");
	jetRawEn_in    = tree_input . GetPtrFloat ("jetRawEn");
	jetCHF_in      = tree_input . GetPtrFloat ("jetCHF");
	jetNHF_in      = tree_input . GetPtrFloat ("jetNHF");
	jetCEF_in      = tree_input . GetPtrFloat ("jetCEF");
	jetNEF_in      = tree_input . GetPtrFloat ("jetNEF");
	jetNCH_in      = tree_input . GetPtrInt   ("jetNCH");
	jetNNP_in      = tree_input . GetPtrInt   ("jetNNP");
	jetMUF_in      = tree_input . GetPtrFloat ("jetMUF");
	jetPUFullID_in = tree_input . GetPtrInt   ("jetPUFullID");
	jetJECUnc_in   = tree_input . GetPtrFloat ("jetJECUnc");
	if (isMC)
	{
		jetP4Smear_in   = tree_input . GetPtrFloat ("jetP4Smear");
		jetP4SmearUp_in = tree_input . GetPtrFloat ("jetP4SmearUp");
		jetP4SmearDo_in = tree_input . GetPtrFloat ("jetP4SmearDo");
	}

	// * Fill the containers
	nJet_out = nJet_in;

	for (int i=0; i<nJet_out; i++)
	{
		jetPt_out        . push_back (jetPt_in[i]);
		jetRawPt_out     . push_back (jetRawPt_in[i]);
		jetEta_out       . push_back (jetEta_in[i]);
		jetPhi_out       . push_back (jetPhi_in[i]);
		jetEn_out        . push_back (jetEn_in[i]);
		jetRawEn_out     . push_back (jetRawEn_in[i]);
		jetChHFrac_out   . push_back (jetCHF_in[i]);
		jetNeuHFrac_out  . push_back (jetNHF_in[i]);
		jetChEMFrac_out  . push_back (jetCEF_in[i]);
		jetNeuEMFrac_out . push_back (jetNEF_in[i]);
		jetNCharged_out  . push_back (jetNCH_in[i]);
		jetNNeutral_out  . push_back (jetNNP_in[i]);
		jetMuonFrac_out  . push_back (jetMUF_in[i]);
		jetPUFullID_out  . push_back (jetPUFullID_in[i]);
		jetJECUnc_out    . push_back (jetJECUnc_in[i]);

		jetSmear   = (isMC) ? jetP4Smear_in[i] : 1.0;
		jetSmearUp = (isMC) ? jetP4SmearUp_in[i] : 1.0;
		jetSmearDo = (isMC) ? jetP4SmearDo_in[i] : 1.0;

		jetP4Smear_out   . push_back (jetSmear);
		jetP4SmearUp_out . push_back (jetSmearUp);
		jetP4SmearDo_out . push_back (jetSmearDo);
	}
}

#endif
