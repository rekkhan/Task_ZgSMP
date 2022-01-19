#ifndef TREEPRESELECT_ELECTRON_H
#define TREEPRESELECT_ELECTRON_H


#include "../Utility/untuplizer_v09.h"


// + List of input variables
//--------------------------
int      nEle_in;
Short_t *eleIDbit_in;
int     *eleCharge_in;
float   *elePt_in;
float   *eleCalibPt_in;
float   *eleEta_in;
float   *eleSCEta_in;
float   *elePhi_in;
float   *eleSCPhi_in;
float   *eleEn_in;
float   *eleCalibEn_in;
float   *eleD0_in;
float   *eleDz_in;


// + List of output variables
//---------------------------
int            nEle_out;
vector<int>    eleCharge_out;
vector<float>  elePt_out;
vector<float>  eleCalibPt_out;
vector<float>  eleEta_out;
vector<float>  eleSCEta_out;
vector<float>  elePhi_out;
vector<float>  eleSCPhi_out;
vector<float>  eleEn_out;
vector<float>  eleCalibEn_out;
vector<float>  eleD0_out;
vector<float>  eleDz_out;
vector<int>    elePass_out;


// + Define branch
//----------------
void  BranchPreselect_Electron (TTree* tree_output)
{
	tree_output -> Branch ("nEle",       &nEle_out);
	tree_output -> Branch ("eleCharge",  &eleCharge_out);
	tree_output -> Branch ("elePt",      &elePt_out);
	tree_output -> Branch ("eleCalibPt", &eleCalibPt_out);
	tree_output -> Branch ("eleEta",     &eleEta_out);
	tree_output -> Branch ("eleSCEta",   &eleSCEta_out);
	tree_output -> Branch ("elePhi",     &elePhi_out);
	tree_output -> Branch ("eleSCPhi",   &eleSCPhi_out);
	tree_output -> Branch ("eleEn",      &eleEn_out);
	tree_output -> Branch ("eleCalibEn", &eleCalibEn_out);
	tree_output -> Branch ("eleD0",      &eleD0_out);
	tree_output -> Branch ("eleDz",      &eleDz_out);
	tree_output -> Branch ("elePass",    &elePass_out);
}


// + Fill output
//--------------
int    nEle_pass;
int    nEle_highPt;

bool   elePass;
float  eleAbsEta;

int  FillPreselect_Electron (TreeReader &tree_input)
{
	nEle_out       = 0;
	eleCharge_out  . clear();
	elePt_out      . clear();
	eleCalibPt_out . clear();
	eleEta_out     . clear();
	eleSCEta_out   . clear();
	elePhi_out     . clear();
	eleSCPhi_out   . clear();
	eleEn_out      . clear();
	eleCalibEn_out . clear();
	eleD0_out      . clear();
	eleDz_out      . clear();
	elePass_out    . clear();

	nEle_in       = tree_input . GetInt      ("nEle");
	if (nEle_in < 2)   return 0;

	eleIDbit_in   = tree_input . GetPtrShort ("eleIDbit");
	eleCharge_in  = tree_input . GetPtrInt   ("eleCharge");
	elePt_in      = tree_input . GetPtrFloat ("elePt");
	eleCalibPt_in = tree_input . GetPtrFloat ("eleCalibPt");
	eleEta_in     = tree_input . GetPtrFloat ("eleEta");
	eleSCEta_in   = tree_input . GetPtrFloat ("eleSCEta");
	elePhi_in     = tree_input . GetPtrFloat ("elePhi");
	eleSCPhi_in   = tree_input . GetPtrFloat ("eleSCPhi");
	eleEn_in      = tree_input . GetPtrFloat ("eleEn");
	eleCalibEn_in = tree_input . GetPtrFloat ("eleCalibEn");
	eleD0_in      = tree_input . GetPtrFloat ("eleD0");
	eleDz_in      = tree_input . GetPtrFloat ("eleDz");

	nEle_out    = nEle_in;
	nEle_pass   = 0;
	nEle_highPt = 0;

	for (int i=0; i<nEle_out; i++)
	{
		eleAbsEta = abs (eleSCEta_in[i]);

		elePass  = ((eleIDbit_in[i]>>3) & 1);
		elePass &= (eleCalibPt_in[i] > 20);
		elePass &= ((eleAbsEta<2.4 && eleAbsEta>1.566) || eleAbsEta<1.4442);

		nEle_pass   += (elePass);
		nEle_highPt += (eleCalibPt_in[i]>25);

		eleCharge_out  . push_back (eleCharge_in[i]);
		elePt_out      . push_back (elePt_in[i]);
		eleCalibPt_out . push_back (eleCalibPt_in[i]);
		eleEta_out     . push_back (eleEta_in[i]);
		eleSCEta_out   . push_back (eleSCEta_in[i]);
		elePhi_out     . push_back (elePhi_in[i]);
		eleSCPhi_out   . push_back (eleSCPhi_in[i]);
		eleEn_out      . push_back (eleEn_in[i]);
		eleCalibEn_out . push_back (eleCalibEn_in[i]);
		eleD0_out      . push_back (eleD0_in[i]);
		eleDz_out      . push_back (eleDz_in[i]);
		elePass_out    . push_back (elePass);
	}

	if (nEle_highPt<1 || nEle_pass<2)   return 0;

	return 1;
}


#endif
