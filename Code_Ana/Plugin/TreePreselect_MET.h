#ifndef TREEPRESELECT_MET_H
#define TREEPRESELECT_MET_H


#include "../Utility/untuplizer_v09.h"
#include "../Utility/Correction_METXYUltralegacy.h"

using namespace std;


// * Input variables
int    metFilters;
float  pfMET;
float  pfMETPhi;
float  pfXYCorMET;
float  pfXYCorMETPhi;


// + Define branches
//------------------
void BranchPreselect_MET (TTree *tree_output)
{
	tree_output -> Branch ("metFilters",    &metFilters);
	tree_output -> Branch ("pfMET",         &pfMET);
	tree_output -> Branch ("pfMETPhi",      &pfMETPhi);
	tree_output -> Branch ("pfXYCorMET",    &pfXYCorMET);
	tree_output -> Branch ("pfXYCorMETPhi", &pfXYCorMETPhi);
}


// + Fill output
//--------------
int  FillPreselect_MET (TreeReader &tree_input,  bool isMC, int year, int run, int nVtx, int reproc)
{
	// * Read variables form input
	metFilters = tree_input . GetInt   ("metFilters");
	pfMET      = tree_input . GetFloat ("pfMET");
	pfMETPhi   = tree_input . GetFloat ("pfMETPhi");

	bool isUL = (reproc==2);

	TString strYear = Form ("%d", year);
	pair<double,double>  correctorXY;
	correctorXY = METXYCorr_Met_MetPhi (pfMET, pfMETPhi, run, strYear, isMC, nVtx, isUL, false);

	pfXYCorMET    = correctorXY . first;
	pfXYCorMETPhi = correctorXY . second;

	return 1;
}


#endif
