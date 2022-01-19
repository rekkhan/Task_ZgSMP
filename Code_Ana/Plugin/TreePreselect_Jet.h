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
bool jetPass;
bool jettightID;

bool jettightTmp;
bool jettight16UL;
bool jettight17UL;
bool jettight18UL;
bool jettight16LR;
bool jettight17LR;
bool jettight18LR;

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
		// + JetID 2016 UL
		//----------------
		jettight16UL  = false;

		// * 0 < eta < 2.4
		jettightTmp  = (abs(jetEta_in[i]) <= 2.4);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettightTmp &= (jetChHFrac_in[i] > 0);
		jettightTmp &= (jetNCharged_in[i] > 0);
		jettightTmp &= jetChEMFrac_in[i] < 0.80;
		jettight16UL |= jettightTmp;

		// * 2.4 < eta < 2.7
		jettightTmp  = (abs(jetEta_in[i])>2.4 && abs(jetEta_in[i])<=2.7);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.99);
		jettight16UL |= jettightTmp;

		// * 2.7 < eta < 3.0
		jettightTmp  = (abs(jetEta_in[i])>2.7 && abs(jetEta_in[i])<=3.0);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i]>0.00 && jetNeuEMFrac_in[i]<0.99);
		jettightTmp &= (jetNNeutral_in[i] > 1);
		jettight16UL |= jettightTmp;

		// * 3.0 < eta < 5.0
		jettightTmp  = (abs(jetEta_in[i])>3.0 && abs(jetEta_in[i])<=5.0);
		jettightTmp &= (jetNeuHFrac_in[i] > 0.2);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= (jetNNeutral_in[i] > 10);
		jettight16UL |= jettightTmp;

		jettight16UL &= (reproc==2 && year==2016);


		// + JetID 2017 UL
		//----------------
		jettight17UL = false;

		// * 0 < eta < 2.4
		jettightTmp  = (abs(jetEta_in[i]) <= 2.6);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettightTmp &= (jetChHFrac_in[i] > 0);
		jettightTmp &= (jetNCharged_in[i] > 0);
		jettightTmp &= jetChEMFrac_in[i] < 0.80;
		jettight17UL |= jettightTmp;

		// * 2.4 < eta < 2.7
		jettightTmp  = (abs(jetEta_in[i])>2.6 && abs(jetEta_in[i])<=2.7);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.99);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettightTmp &= (jetNCharged_in[i] > 0);
		jettightTmp &= jetChEMFrac_in[i] < 0.80;
		jettight17UL |= jettightTmp;

		// * 2.7 < eta < 3.0
		jettightTmp  = (abs(jetEta_in[i])>2.7 && abs(jetEta_in[i])<=3.0);
		jettightTmp &= (jetNeuEMFrac_in[i]>0.01 && jetNeuEMFrac_in[i]<0.99);
		jettightTmp &= (jetNNeutral_in[i] > 1);
		jettight17UL |= jettightTmp;

		// * 3.0 < eta < 5.0
		jettightTmp  = (abs(jetEta_in[i])>3.0 && abs(jetEta_in[i])<=5.0);
		jettightTmp &= (jetNeuHFrac_in[i] > 0.2);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= (jetNNeutral_in[i] > 10);
		jettight17UL |= jettightTmp;

		jettight17UL &= (reproc==2 && year==2017);


		// + JetID 2018 UL
		//----------------
		jettight18UL = false;

		// * 2018UL is just a copy of 2017UL
		jettight18UL &= jettight17UL;

		jettight18UL &= (reproc==2 && year==2018);


		// + JetID 2016 LR
		//----------------
		jettight16LR  = false;

		// * 0 < eta < 2.4
		jettightTmp  = (abs(jetEta_in[i]) <= 2.4);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettightTmp &= (jetChHFrac_in[i] > 0);
		jettightTmp &= (jetNCharged_in[i] > 0);
		jettightTmp &= jetChEMFrac_in[i] < 0.90;
		jettight16LR |= jettightTmp;

		// * 2.4 < eta < 2.7
		jettightTmp  = (abs(jetEta_in[i])>2.4 && abs(jetEta_in[i])<=2.7);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettight16LR |= jettightTmp;

		// * 2.7 < eta < 3.0
		jettightTmp  = (abs(jetEta_in[i])>2.7 && abs(jetEta_in[i])<=3.0);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.98);
		jettightTmp &= (jetNeuEMFrac_in[i] > 0.01);
		jettightTmp &= (jetNNeutral_in[i] > 2);
		jettight16LR |= jettightTmp;

		// * 3.0 < eta
		jettightTmp  = (abs(jetEta_in[i])>3.0);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= (jetNNeutral_in[i] > 10);
		jettight16LR |= jettightTmp;

		jettight16LR &= (reproc==1 && year==2016);


		// + JetID 2017 LR
		//----------------
		jettight17LR = false;

		// * 0 < eta < 2.4
		jettightTmp  = (abs(jetEta_in[i]) <= 2.4);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettightTmp &= (jetChHFrac_in[i] > 0);
		jettightTmp &= (jetNCharged_in[i] > 0);
		jettightTmp &= jetChEMFrac_in[i] < 0.80;
		jettight17LR |= jettightTmp;

		// * 2.4 < eta < 2.7
		jettightTmp  = (abs(jetEta_in[i])>2.4 && abs(jetEta_in[i])<=2.7);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettight17LR |= jettightTmp;

		// * 2.7 < eta < 3.0
		jettightTmp  = (abs(jetEta_in[i])>2.7 && abs(jetEta_in[i])<=3.0);
		jettightTmp &= (jetNeuEMFrac_in[i] > 0.02) && (jetNeuEMFrac_in[i] < 0.99);
		jettightTmp &= (jetNNeutral_in[i] > 2);
		jettight17LR |= jettightTmp;

		// * 3.0 < eta
		jettightTmp  = (abs(jetEta_in[i])>3.0);
		jettightTmp &= (jetNeuHFrac_in[i] > 0.02);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= (jetNNeutral_in[i] > 10);
		jettight17LR |= jettightTmp;

		jettight17LR &= (reproc==1 && year==2017);


		// + JetID 2018 LR
		//----------------
		jettight18LR = false;

		// * 0 < eta < 2.4
		jettightTmp  = (abs(jetEta_in[i]) <= 2.6);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= ((jetNCharged_in[i] + jetNNeutral_in[i]) > 1);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettightTmp &= (jetChHFrac_in[i] > 0);
		jettightTmp &= (jetNCharged_in[i] > 0);
		jettightTmp &= jetChEMFrac_in[i] < 0.80;
		jettight18LR |= jettightTmp;

		// * 2.4 < eta < 2.7
		jettightTmp  = (abs(jetEta_in[i])>2.6 && abs(jetEta_in[i])<=2.7);
		jettightTmp &= (jetNeuHFrac_in[i] < 0.90);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.99);
		jettightTmp &= (jetMuonFrac_in[i] < 0.80);
		jettightTmp &= (jetNCharged_in[i] > 0);
		jettightTmp &= jetChEMFrac_in[i] < 0.80;
		jettight18LR |= jettightTmp;

		// * 2.7 < eta < 3.0
		jettightTmp  = (abs(jetEta_in[i])>2.7 && abs(jetEta_in[i])<=3.0);
		jettightTmp &= (jetNeuEMFrac_in[i]>0.02 && jetNeuEMFrac_in[i]<0.99);
		jettightTmp &= (jetNNeutral_in[i] > 2);
		jettight18LR |= jettightTmp;

		// * 3.0 < eta < 5.0
		jettightTmp  = (abs(jetEta_in[i])>3.0 && abs(jetEta_in[i])<=5.0);
		jettightTmp &= (jetNeuHFrac_in[i] > 0.2);
		jettightTmp &= (jetNeuEMFrac_in[i] < 0.90);
		jettightTmp &= (jetNNeutral_in[i] > 10);
		jettight18LR |= jettightTmp;

		jettight18LR &= (reproc==1 && year==2018);


		// + Jet passing tight ID
		//-----------------------
		jettightID  = false;
		jettightID |= jettight16LR;
		jettightID |= jettight17LR;
		jettightID |= jettight18LR;
		jettightID |= jettight16UL;
		jettightID |= jettight17UL;
		jettightID |= jettight18UL;


		// + Pass condition for jets
		//--------------------------
		jetPass  = jettightID;
		jetPass &= (jetPt_in[i] > 30);
		jetPass &= (jetEta_in[i] > 2.4);

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
