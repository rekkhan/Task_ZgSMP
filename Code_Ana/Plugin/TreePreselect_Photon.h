#ifndef TREEPRESELECT_PHOTON_H
#define TREEPRESELECT_PHOTON_H


#include "../Utility/untuplizer_v09.h"
#include "../Utility/Calculator.h"

using namespace std;


// + list of input variable
//-------------------------
Int_t  nPho_in;
float *phoEt_in;
float *phoCalibEt_in;
float *phoEta_in;
float *phoSCEta_in;
float *phoPhi_in;
float *phoSCPhi_in;
float *phoE_in;
float *phoPFChIso_in;
float *phoPFChWorstIso_in;
float *phoPFPhoIso_in;
int   *phoEleVeto_in;
int   *phohasPixelSeed_in;
float *phoHoverE_in;
float *phoSCRawE_in;
float *phoESEnP1_in;
float *phoESEnP2_in;
float *phoSCEtaWidth_in;
float *phoSCPhiWidth_in;
float *phoESEffSigmaRR_in;
float *phoR9_in;
float *phoSigmaIEtaIEtaFull_in;
float *phoSigmaIEtaIPhiFull_in;
float *phoE2x2Full_in;
float *phoE5x5Full_in;
float *phoScale_stat_up_in;
float *phoScale_stat_dn_in;
float *phoScale_syst_up_in;
float *phoScale_syst_dn_in;
float *phoScale_gain_up_in;
float *phoScale_gain_dn_in;
float *phoResol_rho_up_in;
float *phoResol_rho_dn_in;
float *phoResol_phi_up_in;
float *phoResol_phi_dn_in;

float  rhotmp;


// + List of output variables
//---------------------------
Int_t          nPho_out;
vector<float>  phoEt_out;
vector<float>  phoCalibEt_out;
vector<float>  phoEta_out;
vector<float>  phoSCEta_out;
vector<float>  phoPhi_out;
vector<float>  phoSCPhi_out;
vector<float>  phoE_out;
vector<float>  phoPFChIso_out;
vector<float>  phoPFChWorstIso_out;
vector<float>  phoPFPhoIso_out;
vector<int>    phoEleVeto_out;
vector<int>    phohasPixelSeed_out;
vector<float>  phoHoverE_out;
vector<float>  phoSCRawE_out;
vector<float>  phoESEnP1_out;
vector<float>  phoESEnP2_out;
vector<float>  phoSCEtaWidth_out;
vector<float>  phoSCPhiWidth_out;
vector<float>  phoESEffSigmaRR_out;
vector<float>  phoR9_out;
vector<float>  phoSigmaIEtaIEtaFull_out;
vector<float>  phoSigmaIEtaIPhiFull_out;
vector<float>  phoE2x2Full_out;
vector<float>  phoE5x5Full_out;
vector<float>  phoScale_stat_up_out;
vector<float>  phoScale_stat_dn_out;
vector<float>  phoScale_syst_up_out;
vector<float>  phoScale_syst_dn_out;
vector<float>  phoScale_gain_up_out;
vector<float>  phoScale_gain_dn_out;
vector<float>  phoResol_rho_up_out;
vector<float>  phoResol_rho_dn_out;
vector<float>  phoResol_phi_up_out;
vector<float>  phoResol_phi_dn_out;
vector<int>    phoPass_out;


// + Define branches
//------------------
void  BranchPreselect_Photon (TTree *tree_output)
{
	tree_output -> Branch ("nPho",                 &nPho_out);
	tree_output -> Branch ("phoEt",                &phoEt_out);
	tree_output -> Branch ("phoCalibEt",           &phoCalibEt_out);
	tree_output -> Branch ("phoEta",               &phoEta_out);
	tree_output -> Branch ("phoSCEta",             &phoSCEta_out);
	tree_output -> Branch ("phoPhi",               &phoPhi_out);
	tree_output -> Branch ("phoSCPhi",             &phoSCPhi_out);
	tree_output -> Branch ("phoE",                 &phoE_out);
	tree_output -> Branch ("phoPFChIso",           &phoPFChIso_out);
	tree_output -> Branch ("phoPFChWorstIso",      &phoPFChWorstIso_out);
	tree_output -> Branch ("phoPFPhoIso",          &phoPFPhoIso_out);
	tree_output -> Branch ("phoEleVeto",           &phoEleVeto_out);
	tree_output -> Branch ("phohasPixelSeed",      &phohasPixelSeed_out);
	tree_output -> Branch ("phoHoverE",            &phoHoverE_out);
	tree_output -> Branch ("phoSCRawE",            &phoSCRawE_out);
	tree_output -> Branch ("phoESEnP1",            &phoESEnP1_out);
	tree_output -> Branch ("phoESEnP2",            &phoESEnP2_out);
	tree_output -> Branch ("phoSCEtaWidth",        &phoSCEtaWidth_out);
	tree_output -> Branch ("phoSCPhiWidth",        &phoSCPhiWidth_out);
	tree_output -> Branch ("phoESEffSigmaRR",      &phoESEffSigmaRR_out);
	tree_output -> Branch ("phoR9",                &phoR9_out);
	tree_output -> Branch ("phoSigmaIEtaIEtaFull", &phoSigmaIEtaIEtaFull_out);
	tree_output -> Branch ("phoSigmaIEtaIPhiFull", &phoSigmaIEtaIPhiFull_out);
	tree_output -> Branch ("phoE2x2Full",          &phoE2x2Full_out);
	tree_output -> Branch ("phoE5x5Full",          &phoE5x5Full_out);
	tree_output -> Branch ("phoScale_stat_up",     &phoScale_stat_up_out);
	tree_output -> Branch ("phoScale_stat_dn",     &phoScale_stat_dn_out);
	tree_output -> Branch ("phoScale_syst_up",     &phoScale_syst_up_out);
	tree_output -> Branch ("phoScale_syst_dn",     &phoScale_syst_dn_out);
	tree_output -> Branch ("phoScale_gain_up",     &phoScale_gain_up_out);
	tree_output -> Branch ("phoScale_gain_dn",     &phoScale_gain_dn_out);
	tree_output -> Branch ("phoResol_rho_up",      &phoResol_rho_up_out);
	tree_output -> Branch ("phoResol_rho_dn",      &phoResol_rho_dn_out);
	tree_output -> Branch ("phoResol_phi_up",      &phoResol_phi_up_out);
	tree_output -> Branch ("phoResol_phi_dn",      &phoResol_phi_dn_out);
	tree_output -> Branch ("phoPass",              &phoPass_out);
}


// + Fill output
//--------------
int    nPho_pass;

float  phoAbsEta;
bool   isEB;

float  corIsoPho;
float  corIsoCh;

float  areaEff[2][7] =
{
	{0.0112, 0.0108, 0.0106, 0.01002, 0.0098, 0.0089},
	{0.1113, 0.0953, 0.0619, 0.08370, 0.1070, 0.1212}
};
float  eaSCEta[6] = {1.0, 1.479, 2.0, 2.2, 2.3, 2.4};

int  FillPreselect_Photon (TreeReader &tree_input,  bool isMC,  bool rejPho)
{
	// * Clean the containers
	nPho_out                 = 0;
	phoEt_out                . clear();
	phoCalibEt_out           . clear();
	phoEta_out               . clear();
	phoSCEta_out             . clear();
	phoPhi_out               . clear();
	phoSCPhi_out             . clear();
	phoE_out                 . clear();
	phoPFChIso_out           . clear();
	phoPFChWorstIso_out      . clear();
	phoPFPhoIso_out          . clear();
	phoEleVeto_out           . clear();
	phohasPixelSeed_out      . clear();
	phoHoverE_out            . clear();
	phoSCRawE_out            . clear();
	phoESEnP1_out            . clear();
	phoESEnP2_out            . clear();
	phoSCEtaWidth_out        . clear();
	phoSCPhiWidth_out        . clear();
	phoESEffSigmaRR_out      . clear();
	phoR9_out                . clear();
	phoSigmaIEtaIEtaFull_out . clear();
	phoSigmaIEtaIPhiFull_out . clear();
	phoE2x2Full_out          . clear();
	phoE5x5Full_out          . clear();
	phoScale_stat_up_out     . clear();
	phoScale_stat_dn_out     . clear();
	phoScale_syst_up_out     . clear();
	phoScale_syst_dn_out     . clear();
	phoScale_gain_up_out     . clear();
	phoScale_gain_dn_out     . clear();
	phoResol_rho_up_out      . clear();
	phoResol_rho_dn_out      . clear();
	phoResol_phi_up_out      . clear();
	phoResol_phi_dn_out      . clear();
	phoPass_out              . clear();

	// * Read variables from input
	nPho_in                 = tree_input . GetInt      ("nPho");
	if (nPho_in < 1)   return 0;

	phoEt_in                = tree_input . GetPtrFloat ("phoEt");
	phoCalibEt_in           = tree_input . GetPtrFloat ("phoCalibEt");
	phoEta_in               = tree_input . GetPtrFloat ("phoEta");
	phoSCEta_in             = tree_input . GetPtrFloat ("phoSCEta");
	phoPhi_in               = tree_input . GetPtrFloat ("phoPhi");
	phoSCPhi_in             = tree_input . GetPtrFloat ("phoSCPhi");
	phoE_in                 = tree_input . GetPtrFloat ("phoE");
	phoPFChIso_in           = tree_input . GetPtrFloat ("phoPFChIso");
	phoPFChWorstIso_in      = tree_input . GetPtrFloat ("phoPFChWorstIso");
	phoPFPhoIso_in          = tree_input . GetPtrFloat ("phoPFPhoIso");
	phoEleVeto_in           = tree_input . GetPtrInt   ("phoEleVeto");
	phohasPixelSeed_in      = tree_input . GetPtrInt   ("phohasPixelSeed");
	phoHoverE_in            = tree_input . GetPtrFloat ("phoHoverE");
	phoSCRawE_in            = tree_input . GetPtrFloat ("phoSCRawE");
	phoESEnP1_in            = tree_input . GetPtrFloat ("phoESEnP1");
	phoESEnP2_in            = tree_input . GetPtrFloat ("phoESEnP2");
	phoSCEtaWidth_in        = tree_input . GetPtrFloat ("phoSCEtaWidth");
	phoSCPhiWidth_in        = tree_input . GetPtrFloat ("phoSCPhiWidth");
	phoESEffSigmaRR_in      = tree_input . GetPtrFloat ("phoESEffSigmaRR");
	phoR9_in                = tree_input . GetPtrFloat ("phoR9");
	phoSigmaIEtaIEtaFull_in = tree_input . GetPtrFloat ("phoSigmaIEtaIEtaFull");
	phoSigmaIEtaIPhiFull_in = tree_input . GetPtrFloat ("phoSigmaIEtaIPhiFull");
	phoE2x2Full_in          = tree_input . GetPtrFloat ("phoE2x2Full");
	phoE5x5Full_in          = tree_input . GetPtrFloat ("phoE5x5Full");
	phoScale_stat_up_in     = tree_input . GetPtrFloat ("phoScale_stat_up");
	phoScale_stat_dn_in     = tree_input . GetPtrFloat ("phoScale_stat_dn");
	phoScale_syst_up_in     = tree_input . GetPtrFloat ("phoScale_syst_up");
	phoScale_syst_dn_in     = tree_input . GetPtrFloat ("phoScale_syst_dn");
	phoScale_gain_up_in     = tree_input . GetPtrFloat ("phoScale_gain_up");
	phoScale_gain_dn_in     = tree_input . GetPtrFloat ("phoScale_gain_dn");
	phoResol_rho_up_in      = tree_input . GetPtrFloat ("phoResol_rho_up");
	phoResol_rho_dn_in      = tree_input . GetPtrFloat ("phoResol_rho_dn");
	phoResol_phi_up_in      = tree_input . GetPtrFloat ("phoResol_phi_up");
	phoResol_phi_dn_in      = tree_input . GetPtrFloat ("phoResol_phi_dn");

	rhotmp = tree_input . GetFloat ("rho");

	int    nMC_in;
	short *mcStatusFlag_in;
	int   *mcPID_in;
	float *mcEta_in;
	float *mcPhi_in;

	if (isMC)
	{
		nMC_in          = tree_input . GetInt      ("nMC");
		mcStatusFlag_in = tree_input . GetPtrShort ("mcStatusFlag");
		mcPID_in        = tree_input . GetPtrInt   ("mcPID");
		mcEta_in        = tree_input . GetPtrFloat ("mcEta");
		mcPhi_in        = tree_input . GetPtrFloat ("mcPhi");
	}

	// * Fill the containers
	nPho_out   = nPho_in;
	nPho_pass  = 0;

	double  cal_dR;

	bool   phoMatchGen;
	bool   phoPass;

	for (int i=0; i<nPho_out; i++)
	{
		phoMatchGen = false;
		if (isMC && rejPho)
		{
			for (int j=0; j<nMC_in; j++)
			{
				if (abs(mcPID_in[j]) != 22)   continue;
				if (((mcStatusFlag_in[j]>>0)&1)==false && ((mcStatusFlag_in[j]>>1)&1)==false)   continue;
				cal_dR = compute_DeltaR (phoEta_in[i], mcEta_in[j], phoPhi_in[i], mcPhi_in[j]);
				phoMatchGen = cal_dR < 0.1;

				if (phoMatchGen)
				{
					//printf ("  |   |   |-- A photon is matched to gen level\n");
					return 2;
				}
			}
		}

		if (phoMatchGen)
		{
			nPho_pass = 0;
			break;
		}

		int binEta = 0;

		while (binEta < 6)
		{
			if (abs(phoSCEta_in[i]) < eaSCEta[binEta])   break;
			binEta ++;
		}

		corIsoCh  = (binEta<6) ? max (float(phoPFChIso_in[i]-rhotmp*areaEff[0][binEta]), (float)0.0) : phoPFChIso_in[i];
		corIsoPho = (binEta<6) ? max (float(phoPFPhoIso_in[i]-rhotmp*areaEff[1][binEta]), (float)0.0) : phoPFPhoIso_in[i];
		isEB      = (abs(phoSCEta_in[i]) < 1.4442);

		phoPass  = (phoCalibEt_in[i] > 20);
		phoPass &= (abs(phoSCEta_in[i])<1.4442 || (abs(phoSCEta_in[i])>1.566 && abs(phoSCEta_in[i])<2.4));
		phoPass &= (phoEleVeto_in[i] == 1);
		phoPass &= ((isEB) ? phoHoverE_in[i]<0.08 : phoHoverE_in[i]<0.05);
		phoPass &= ((isEB) ? phoSigmaIEtaIEtaFull_in[i]<0.015 : phoSigmaIEtaIEtaFull_in[i]<0.045);
		phoPass &= (corIsoPho < 15.0);
		phoPass &= (corIsoCh < 15.0);

		nPho_pass += (phoPass) ? 1 : 0;

		phoEt_out                . push_back (phoEt_in[i]);
		phoCalibEt_out           . push_back (phoCalibEt_in[i]);
		phoEta_out               . push_back (phoEta_in[i]);
		phoSCEta_out             . push_back (phoSCEta_in[i]);
		phoPhi_out               . push_back (phoPhi_in[i]);
		phoSCPhi_out             . push_back (phoSCPhi_in[i]);
		phoE_out                 . push_back (phoE_in[i]);
		phoPFChIso_out           . push_back (corIsoCh);
		phoPFChWorstIso_out      . push_back (corIsoPho);
		phoPFPhoIso_out          . push_back (phoPFPhoIso_in[i]);
		phoEleVeto_out           . push_back (phoEleVeto_in[i]);
		phohasPixelSeed_out      . push_back (phohasPixelSeed_in[i]);
		phoHoverE_out            . push_back (phoHoverE_in[i]);
		phoSCRawE_out            . push_back (phoSCRawE_in[i]);
		phoESEnP1_out            . push_back (phoESEnP1_in[i]);
		phoESEnP2_out            . push_back (phoESEnP2_in[i]);
		phoSCEtaWidth_out        . push_back (phoSCEtaWidth_in[i]);
		phoSCPhiWidth_out        . push_back (phoSCPhiWidth_in[i]);
		phoESEffSigmaRR_out      . push_back (phoESEffSigmaRR_in[i]);
		phoR9_out                . push_back (phoR9_in[i]);
		phoSigmaIEtaIEtaFull_out . push_back (phoSigmaIEtaIEtaFull_in[i]);
		phoSigmaIEtaIPhiFull_out . push_back (phoSigmaIEtaIPhiFull_in[i]);
		phoE2x2Full_out          . push_back (phoE2x2Full_in[i]);
		phoE5x5Full_out          . push_back (phoE5x5Full_in[i]);
		phoScale_stat_up_out     . push_back (phoScale_stat_up_in[i]);
		phoScale_stat_dn_out     . push_back (phoScale_stat_dn_in[i]);
		phoScale_syst_up_out     . push_back (phoScale_syst_up_in[i]);
		phoScale_syst_dn_out     . push_back (phoScale_syst_dn_in[i]);
		phoScale_gain_up_out     . push_back (phoScale_gain_up_in[i]);
		phoScale_gain_dn_out     . push_back (phoScale_gain_dn_in[i]);
		phoResol_rho_up_out      . push_back (phoResol_rho_up_in[i]);
		phoResol_rho_dn_out      . push_back (phoResol_rho_dn_in[i]);
		phoResol_phi_up_out      . push_back (phoResol_phi_up_in[i]);
		phoResol_phi_dn_out      . push_back (phoResol_phi_dn_in[i]);
		phoPass_out              . push_back (phoPass);
	}

	if (nPho_pass < 1)   return 0;

	return 1;
}


#endif
