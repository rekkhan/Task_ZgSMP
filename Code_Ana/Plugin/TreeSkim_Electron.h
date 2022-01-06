#ifndef  FILLTREE_ELECTRON_H
#define  FILLTREE_ELECTRON_H

#include "../Utility/untuplizer_v09.h"

// + List of input variable
//-------------------------
Int_t    nEle_in;
int     *eleCharge_in;
float   *elePt_in;
float   *eleCalibPt_in;
float   *eleEta_in;
float   *eleSCEta_in;
float   *elePhi_in;
float   *eleSCPhi_in;
float   *eleEn_in;
float   *eleSCEn_in;
float   *eleCalibEn_in;
float   *eleD0_in;
float   *eleDz_in;
float   *eleSigmaIPhiIPhiFull5x5_in;
float   *eleR9Full5x5_in;
Short_t *eleIDbit_in;
float   *eleSigmaIEtaIEtaFull5x5_in;
float   *eledEtaAtVtx_in;
float   *eledPhiAtVtx_in;
float   *eleHoverE_in;
float   *elePFChIso_in;
float   *elePFPhoIso_in;
float   *elePFNeuIso_in;
float   *elePFPUIso_in;
float   *eleEoverPInv_in;
int     *eleMissHits_in;
int     *eleConvVeto_in;


// + List of output variables
//---------------------------
Int_t            nEle_out;
vector<int>      eleCharge_out;
vector<float>    elePt_out;
vector<float>    eleCalibPt_out;
vector<float>    eleEta_out;
vector<float>    eleSCEta_out;
vector<float>    elePhi_out;
vector<float>    eleSCPhi_out;
vector<float>    eleEn_out;
vector<float>    eleSCEn_out;
vector<float>    eleCalibEn_out;
vector<float>    eleD0_out;
vector<float>    eleDz_out;
vector<float>    eleSigmaIPhiIPhiFull_out;
vector<float>    eleR9Full_out;
vector<Short_t>  eleIDbit_out;
vector<float>    eleSigmaIEtaIEtaFull_out;
vector<float>    eledEtaAtVtx_out;
vector<float>    eledPhiAtVtx_out;
vector<float>    eleHoverE_out;
vector<float>    elePFChIso_out;
vector<float>    elePFPhoIso_out;
vector<float>    elePFNeuIso_out;
vector<float>    elePFPUIso_out;
vector<float>    eleEoverPInv_out;
vector<int>      eleMissHits_out;
vector<int>      eleConvVeto_out;

// + Define branches
//------------------
void  BranchSkim_Electron (TTree *tree_output)
{
	tree_output -> Branch ("nEle",                  &nEle_out);
	tree_output -> Branch ("eleCharge",             &eleCharge_out);
	tree_output -> Branch ("elePt",                 &elePt_out);
	tree_output -> Branch ("eleCalibPt",            &eleCalibPt_out);
	tree_output -> Branch ("eleEta",                &eleEta_out);
	tree_output -> Branch ("eleSCEta",              &eleSCEta_out);
	tree_output -> Branch ("elePhi",                &elePhi_out);
	tree_output -> Branch ("eleSCPhi",              &eleSCPhi_out);
	tree_output -> Branch ("eleEn",                 &eleEn_out);
	tree_output -> Branch ("eleSCEn",               &eleSCEn_out);
	tree_output -> Branch ("eleCalibEn",            &eleCalibEn_out);
	tree_output -> Branch ("eleD0",                 &eleD0_out);
	tree_output -> Branch ("eleDz",                 &eleDz_out);
	tree_output -> Branch ("eleSigmaIPhiIPhiFull",  &eleSigmaIPhiIPhiFull_out);
	tree_output -> Branch ("eleR9Full",             &eleR9Full_out);
	tree_output -> Branch ("eleIDbit",              &eleIDbit_out);
	tree_output -> Branch ("eleSigmaIEtaIEtaFull",  &eleSigmaIEtaIEtaFull_out);
	tree_output -> Branch ("eledEtaAtVtx",          &eledEtaAtVtx_out);
	tree_output -> Branch ("eledPhiAtVtx",          &eledPhiAtVtx_out);
	tree_output -> Branch ("eleHoverE",             &eleHoverE_out);
	tree_output -> Branch ("elePFChIso",            &elePFChIso_out);
	tree_output -> Branch ("elePFPhoIso",           &elePFPhoIso_out);
	tree_output -> Branch ("elePFNeuIso",           &elePFNeuIso_out);
	tree_output -> Branch ("elePFPUIso",            &elePFPUIso_out);
	tree_output -> Branch ("eleEoverPInv",          &eleEoverPInv_out);
	tree_output -> Branch ("eleMissHits",           &eleMissHits_out);
	tree_output -> Branch ("eleConvVeto",           &eleConvVeto_out);
}


// + Fill output
//--------------
void  FillSkim_Electron (TreeReader &tree_input)
{
	// * Clean the containers
	nEle_out                 = 0;
	eleCharge_out            . clear();
	elePt_out                . clear();
	eleCalibPt_out           . clear();
	eleEta_out               . clear();
	eleSCEta_out             . clear();
	elePhi_out               . clear();
	eleSCPhi_out             . clear();
	eleEn_out                . clear();
	eleSCEn_out              . clear();
	eleCalibEn_out           . clear();
	eleD0_out                . clear();
	eleDz_out                . clear();
	eleSigmaIPhiIPhiFull_out . clear();
	eleR9Full_out            . clear();
	eleIDbit_out             . clear();
	eleSigmaIEtaIEtaFull_out . clear();
	eledEtaAtVtx_out         . clear();
	eledPhiAtVtx_out         . clear();
	eleHoverE_out            . clear();
	elePFChIso_out           . clear();
	elePFPhoIso_out          . clear();
	elePFNeuIso_out          . clear();
	elePFPUIso_out           . clear();
	eleEoverPInv_out         . clear();
	eleMissHits_out          . clear();
	eleConvVeto_out          . clear();

	// * Read variables from input
	nEle_in = 3;
	nEle_in                    = tree_input . GetInt      ("nEle");
	eleCharge_in               = tree_input . GetPtrInt   ("eleCharge");
	elePt_in                   = tree_input . GetPtrFloat ("elePt");
	eleCalibPt_in              = tree_input . GetPtrFloat ("eleCalibPt");
	eleEta_in                  = tree_input . GetPtrFloat ("eleEta");
	eleSCEta_in                = tree_input . GetPtrFloat ("eleSCEta");
	elePhi_in                  = tree_input . GetPtrFloat ("elePhi");
	eleSCPhi_in                = tree_input . GetPtrFloat ("eleSCPhi");
	eleEn_in                   = tree_input . GetPtrFloat ("eleEn");
	eleSCEn_in                 = tree_input . GetPtrFloat ("eleSCEn");
	eleCalibEn_in              = tree_input . GetPtrFloat ("eleCalibEn");
	eleD0_in                   = tree_input . GetPtrFloat ("eleD0");
	eleDz_in                   = tree_input . GetPtrFloat ("eleDz");
	eleSigmaIPhiIPhiFull5x5_in = tree_input . GetPtrFloat ("eleSigmaIPhiIPhiFull5x5");
	eleR9Full5x5_in            = tree_input . GetPtrFloat ("eleR9Full5x5");
	eleIDbit_in                = tree_input . GetPtrShort ("eleIDbit");
	eleSigmaIEtaIEtaFull5x5_in = tree_input . GetPtrFloat ("eleSigmaIEtaIEtaFull5x5");
	eledEtaAtVtx_in            = tree_input . GetPtrFloat ("eledEtaAtVtx");
	eledPhiAtVtx_in            = tree_input . GetPtrFloat ("eledPhiAtVtx");
	eleHoverE_in               = tree_input . GetPtrFloat ("eleHoverE");
	elePFChIso_in              = tree_input . GetPtrFloat ("elePFChIso");
	elePFPhoIso_in             = tree_input . GetPtrFloat ("elePFPhoIso");
	elePFNeuIso_in             = tree_input . GetPtrFloat ("elePFNeuIso");
	elePFPUIso_in              = tree_input . GetPtrFloat ("elePFPUIso");
	eleEoverPInv_in            = tree_input . GetPtrFloat ("eleEoverPInv");
	eleMissHits_in             = tree_input . GetPtrInt   ("eleMissHits");
	eleConvVeto_in             = tree_input . GetPtrInt   ("eleConvVeto");

	// * Fill the containers
	nEle_out = nEle_in;

	for (int i=0; i<nEle_out; i++)
	{
		eleCharge_out            . push_back (eleCharge_in[i]);
		elePt_out                . push_back (elePt_in[i]);
		eleCalibPt_out           . push_back (eleCalibPt_in[i]);
		eleEta_out               . push_back (eleEta_in[i]);
		eleSCEta_out             . push_back (eleSCEta_in[i]);
		elePhi_out               . push_back (elePhi_in[i]);
		eleSCPhi_out             . push_back (eleSCPhi_in[i]);
		eleEn_out                . push_back (eleEn_in[i]);
		eleSCEn_out              . push_back (eleSCEn_in[i]);
		eleCalibEn_out           . push_back (eleCalibEn_in[i]);
		eleD0_out                . push_back (eleD0_in[i]);
		eleDz_out                . push_back (eleDz_in[i]);
		eleSigmaIPhiIPhiFull_out . push_back (eleSigmaIPhiIPhiFull5x5_in[i]);
		eleR9Full_out            . push_back (eleR9Full5x5_in[i]);
		eleIDbit_out             . push_back (eleIDbit_in[i]);
		eleSigmaIEtaIEtaFull_out . push_back (eleSigmaIEtaIEtaFull5x5_in[i]);
		eledEtaAtVtx_out         . push_back (eledEtaAtVtx_in[i]);
		eledPhiAtVtx_out         . push_back (eledPhiAtVtx_in[i]);
		eleHoverE_out            . push_back (eleHoverE_in[i]);
		elePFChIso_out           . push_back (elePFChIso_in[i]);
		elePFPhoIso_out          . push_back (elePFPhoIso_in[i]);
		elePFNeuIso_out          . push_back (elePFNeuIso_in[i]);
		elePFPUIso_out           . push_back (elePFPUIso_in[i]);
		eleEoverPInv_out         . push_back (eleEoverPInv_in[i]);
		eleMissHits_out          . push_back (eleMissHits_in[i]);
		eleConvVeto_out          . push_back (eleConvVeto_in[i]);
	}
}

#endif
