#ifndef TREEPRESELECT_MUON_H
#define TREEPRESELECT_MUON_H


#include "TRandom3.h"
#include "TMath.h"

#include "../Utility/untuplizer_v09.h"
#include "../Utility/RochesterCorrection/RoccoR.cc"
#include "../Utility/Calculator.h"


// + List of input variables
//--------------------------
int     nMu_in;
int    *muCharge_in;
float  *muPt_in;
float  *muEta_in;
float  *muPhi_in;
float  *muEn_in;
int    *muIDbit_in;
int    *muTrkLayers_in;


// + List of output variables
//------------------------------
int            nMu_out;
vector<int>    muCharge_out;
vector<float>  muPt_out;
vector<float>  muCorPt_out;
vector<float>  muEta_out;
vector<float>  muPhi_out;
vector<float>  muEn_out;
vector<int>    muPass_out;


// + Define branch
//----------------
void  BranchPreselect_Muon (TTree *tree_output)
{
	tree_output -> Branch ("nMu",      &nMu_out);
	tree_output -> Branch ("muCharge", &muCharge_out);
	tree_output -> Branch ("muPt",     &muPt_out);
	tree_output -> Branch ("muCorPt",  &muCorPt_out);
	tree_output -> Branch ("muEta",    &muEta_out);
	tree_output -> Branch ("muPhi",    &muPhi_out);
	tree_output -> Branch ("muEn",     &muEn_out);
	tree_output -> Branch ("muPass",   &muPass_out);
}


// + Fill output
//--------------
TRandom3 *rdGen_Roccor = new TRandom3 (0);

int     nMu_pass;
int     nMu_highPt;
bool    muPass;

float   rc_val;
float   rc_corPT;

int  FillPreselect_Muon (TreeReader &tree_input, RoccoR &rcCore, bool isMC)
{
	nMu_out      = 0;
	muCharge_out . clear();
	muPt_out     . clear();
	muCorPt_out  . clear();
	muEta_out    . clear();
	muPhi_out    . clear();
	muEn_out     . clear();
	muPass_out   . clear();

	nMu_in         = tree_input . GetInt      ("nMu");
	if (nMu_in < 2)  return 0;

	muCharge_in    = tree_input . GetPtrInt   ("muCharge");
	muPt_in        = tree_input . GetPtrFloat ("muPt");
	muEta_in       = tree_input . GetPtrFloat ("muEta");
	muPhi_in       = tree_input . GetPtrFloat ("muPhi");
	muEn_in        = tree_input . GetPtrFloat ("muEn");
	muIDbit_in     = tree_input . GetPtrInt   ("muIDbit");
	muTrkLayers_in = tree_input . GetPtrInt   ("muTrkLayers");

	int     nMC_in;
	int    *mcPID_in;
	float  *mcPt_in;
	float  *mcEta_in;
	float  *mcPhi_in;
	float  *mcE_in;

	if (isMC)
	{
		nMC_in   = tree_input . GetInt      ("nMC");
		mcPID_in = tree_input . GetPtrInt   ("mcPID");
		mcPt_in  = tree_input . GetPtrFloat ("mcPt");
		mcEta_in = tree_input . GetPtrFloat ("mcEta");
		mcPhi_in = tree_input . GetPtrFloat ("mcPhi");
	}

	float   cal_rand;
	double  cal_dR;
	double  cal_dRmin;
	int     cal_iMC;

	nMu_pass   = 0;
	nMu_highPt = 0;
	nMu_out    = nMu_in;

	for (int i=0; i<nMu_in; i++)
	{
		muPass  = (muIDbit_in[i]>>3) & 1;
		muPass &= abs (muEta_in[i]) < 2.4;

		cal_rand  = rdGen_Roccor -> Rndm();
		cal_dRmin = 0.1;

		if (isMC)
		{
			cal_iMC = -1;
			for (int j=0; j<nMC_in; j++)
			{
				if (abs(mcPID_in[j]) != 13)   continue;
				cal_dR = compute_DeltaR (muEta_in[i], mcEta_in[j], muPt_in[i], mcPhi_in[j]);

				if (cal_dR < cal_dRmin)
				{
					cal_iMC   = j;
					cal_dRmin = cal_dR;
				}
			}

			if (cal_iMC > -1)
			{
				rc_val = rcCore . kSpreadMC (muCharge_in[i], muPt_in[i], muEta_in[i], muPhi_in[i], mcPt_in[cal_iMC], 0, 0);
			}
			else
			{
				rc_val = rcCore . kSmearMC (muCharge_in[i], muPt_in[i], muEta_in[i], muPhi_in[i], muTrkLayers_in[i], cal_rand, 0, 0);
			}
		}
		else
		{
			rc_val = rcCore . kScaleDT (muCharge_in[i], muPt_in[i], muEta_in[i], muPt_in[i], 0, 0);
		}

		rc_corPT = muPt_in[i] * rc_val;
		muPass &= rc_corPT > 20.0;

		nMu_highPt += (rc_corPT > 25) ? 1 : 0;
		nMu_pass   += (muPass) ? 1 : 0;

		muCharge_out . push_back (muCharge_in[i]);
		muPt_out     . push_back (muPt_in[i]);
		muCorPt_out  . push_back (rc_corPT);
		muEta_out    . push_back (muEta_in[i]);
		muPhi_out    . push_back (muPhi_in[i]);
		muEn_out     . push_back (muEn_in[i]);
		muPass_out   . push_back (muPass);
	}

	if (nMu_highPt<1 || nMu_pass<2)   return 0;

	return 1;
}


#endif
