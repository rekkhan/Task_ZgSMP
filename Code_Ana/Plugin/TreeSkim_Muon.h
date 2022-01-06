#ifndef  FILLTREE_MUON_H
#define  FILLTREE_MUON_H

#include "../Utility/untuplizer_v09.h"

// + List of input variables
//--------------------------
Int_t   nMu_in;
int    *muCharge_in;
float  *muPt_in;
float  *muEta_in;
float  *muPhi_in;
float  *muEn_in;
int    *muIDbit_in;
int    *muType_in;
float  *muChi2NDF_in;
int    *muMuonHits_in;
int    *muStations_in;
float  *muD0_in;
float  *muDz_in;
float  *muSIP_in;
int    *muPixelHits_in;
int    *muTrkLayers_in;
float  *muIsoTrk_in;
float  *muPFChIso_in;
float  *muPFPhoIso_in;
float  *muPFNeuIso_in;
float  *muPFPUIso_in;


// + List of output variables
//---------------------------
Int_t          nMu_out;
vector<int>    muCharge_out;
vector<float>  muPt_out;
vector<float>  muEta_out;
vector<float>  muPhi_out;
vector<float>  muEn_out;
vector<int>    muIDbit_out;
vector<int>    muType_out;
vector<float>  muChi2NDF_out;
vector<int>    muMuonHits_out;
vector<int>    muStations_out;
vector<float>  muD0_out;
vector<float>  muDz_out;
vector<float>  muSIP_out;
vector<int>    muPixelHits_out;
vector<int>    muTrkLayers_out;
vector<float>  muIsoTrk_out;
vector<float>  muPFChIso_out;
vector<float>  muPFPhoIso_out;
vector<float>  muPFNeuIso_out;
vector<float>  muPFPUIso_out;


// + Define branches
//------------------
void  BranchSkim_Muon (TTree *tree_output)
{
	tree_output -> Branch ("nMu",         &nMu_out);
	tree_output -> Branch ("muCharge",    &muCharge_out);
	tree_output -> Branch ("muPt",        &muPt_out);
	tree_output -> Branch ("muEta",       &muEta_out);
	tree_output -> Branch ("muPhi",       &muPhi_out);
	tree_output -> Branch ("muEn",        &muEn_out);
	tree_output -> Branch ("muIDbit",     &muIDbit_out);
	tree_output -> Branch ("muType",      &muType_out);
	tree_output -> Branch ("muChi2NDF",   &muChi2NDF_out);
	tree_output -> Branch ("muMuonHits",  &muMuonHits_out);
	tree_output -> Branch ("muStations",  &muStations_out);
	tree_output -> Branch ("muD0",        &muD0_out);
	tree_output -> Branch ("muDz",        &muDz_out);
	tree_output -> Branch ("muSIP",       &muSIP_out);
	tree_output -> Branch ("muPixelHits", &muPixelHits_out);
	tree_output -> Branch ("muTrkLayers", &muTrkLayers_out);
	tree_output -> Branch ("muIsoTrk",    &muIsoTrk_out);
	tree_output -> Branch ("muPFChIso",   &muPFChIso_out);
	tree_output -> Branch ("muPFPhoIso",  &muPFPhoIso_out);
	tree_output -> Branch ("muPFNeuIso",  &muPFNeuIso_out);
	tree_output -> Branch ("muPFPUIso",   &muPFPUIso_out);
}


// + Fill output
//--------------
void  FillSkim_Muon (TreeReader &tree_input)
{
	// * Clean the containers
	nMu_out         = 0;
	muCharge_out    . clear();
	muPt_out        . clear();
	muEta_out       . clear();
	muPhi_out       . clear();
	muEn_out        . clear();
	muIDbit_out     . clear();
	muType_out      . clear();
	muChi2NDF_out   . clear();
	muMuonHits_out  . clear();
	muStations_out  . clear();
	muD0_out        . clear();
	muDz_out        . clear();
	muSIP_out       . clear();
	muPixelHits_out . clear();
	muTrkLayers_out . clear();
	muIsoTrk_out    . clear();
	muPFChIso_out   . clear();
	muPFPhoIso_out  . clear();
	muPFNeuIso_out  . clear();
	muPFPUIso_out   . clear();

	// * Read variables from input
	nMu_in         = tree_input . GetInt      ("nMu");
	muCharge_in    = tree_input . GetPtrInt   ("muCharge");
	muPt_in        = tree_input . GetPtrFloat ("muPt");
	muEta_in       = tree_input . GetPtrFloat ("muEta");
	muPhi_in       = tree_input . GetPtrFloat ("muPhi");
	muEn_in        = tree_input . GetPtrFloat ("muEn");
	muIDbit_in     = tree_input . GetPtrInt   ("muIDbit");
	muType_in      = tree_input . GetPtrInt   ("muType");
	muChi2NDF_in   = tree_input . GetPtrFloat ("muChi2NDF");
	muMuonHits_in  = tree_input . GetPtrInt   ("muMuonHits");
	muStations_in  = tree_input . GetPtrInt   ("muStations");
	muD0_in        = tree_input . GetPtrFloat ("muD0");
	muDz_in        = tree_input . GetPtrFloat ("muDz");
	muSIP_in       = tree_input . GetPtrFloat ("muSIP");
	muPixelHits_in = tree_input . GetPtrInt   ("muPixelHits");
	muTrkLayers_in = tree_input . GetPtrInt   ("muTrkLayers");
	muIsoTrk_in    = tree_input . GetPtrFloat ("muIsoTrk");
	muPFChIso_in   = tree_input . GetPtrFloat ("muPFChIso");
	muPFPhoIso_in  = tree_input . GetPtrFloat ("muPFPhoIso");
	muPFNeuIso_in  = tree_input . GetPtrFloat ("muPFNeuIso");
	muPFPUIso_in   = tree_input . GetPtrFloat ("muPFPUIso");

	// * Fill the containers
	nMu_out = nMu_in;

	for (int i=0; i<nMu_out; i++)
	{
		muCharge_out    . push_back (muCharge_in[i]);
		muPt_out        . push_back (muPt_in[i]);
		muEta_out       . push_back (muEta_in[i]);
		muPhi_out       . push_back (muPhi_in[i]);
		muEn_out        . push_back (muEn_in[i]);
		muIDbit_out     . push_back (muIDbit_in[i]);
		muType_out      . push_back (muType_in[i]);
		muChi2NDF_out   . push_back (muChi2NDF_in[i]);
		muMuonHits_out  . push_back (muMuonHits_in[i]);
		muStations_out  . push_back (muStations_in[i]);
		muD0_out        . push_back (muD0_in[i]);
		muDz_out        . push_back (muDz_in[i]);
		muSIP_out       . push_back (muSIP_in[i]);
		muPixelHits_out . push_back (muPixelHits_in[i]);
		muTrkLayers_out . push_back (muTrkLayers_in[i]);
		muIsoTrk_out    . push_back (muIsoTrk_in[i]);
		muPFChIso_out   . push_back (muPFChIso_in[i]);
		muPFPhoIso_out  . push_back (muPFPhoIso_in[i]);
		muPFNeuIso_out  . push_back (muPFNeuIso_in[i]);
		muPFPUIso_out   . push_back (muPFPUIso_in[i]);
	}
}

#endif
