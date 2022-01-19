#ifndef HISTOGRAM_EVENTSELECTION_H
#define HISTOGRAM_EVENTSELECTION_H


#include "../Utility/untuplizer_v09.h"
#include "../Utility/Calculator.h"
#include "TLorentzVector.h"

TH1D *hist_pT_lep1;
TH1D *hist_pT_lep2;
TH1D *hist_pT_pho;
TH1D *hist_pT_jet;
TH1D *hist_pT_inv;

TH1D *hist_eta_lep1;
TH1D *hist_eta_lep2;
TH1D *hist_eta_pho;
TH1D *hist_eta_jet;
TH1D *hist_eta_inv;

TH1D *hist_phi_lep1;
TH1D *hist_phi_lep2;
TH1D *hist_phi_pho;
TH1D *hist_phi_jet;
TH1D *hist_phi_inv;

TH1D *hist_mass_dilep;
TH1D *hist_mass_dileppho;

TH1D *hist_dr_leplep;
TH1D *hist_dr_lep1pho;
TH1D *hist_dr_lep2pho;
TH1D *hist_dr_lep1jet;
TH1D *hist_dr_lep2jet;
TH1D *hist_dr_phojet;

TH1D *hist_chIso_pho;
TH1D *hist_etaeta_pho;
TH1D *hist_etaphi_pho;
TH1D *hist_R9_pho;
TH1D *hist_SCRawE_pho;
TH1D *hist_wEta_pho;
TH1D *hist_wPhi_pho;


void InitHistogram (int leptype)
{
	float binning_lep1Pt[15] =
	{
		0,   10,  25,  35,  45,
		55,  65,  75,  85,  100,
		120, 140, 160, 180, 200
	};

	float binning_lep2Pt[15] =
	{
		0,   10,  20,  30,  40,
		50,  60,  70,  80,  100,
		120, 140, 160, 180, 200
	};

	float binning_phoPt[10] =
	{
		0,  20, 25,  30,  35,
		40, 50, 100, 150, 200
	};

	float binning_jetPt[10] =
	{
		0,  20, 25,  30,  35,
		40, 50, 100, 150, 200
	};

	float binning_invPt[15] =
	{
		0,  5,  10, 15,  20,
		25, 30, 35, 40,  45,
		50, 60, 80, 100, 200
	};

	float binning_mass2[25] =
	{
		30,  35,  40,  45,  50,
		55,  60,  65,  70,  75,
		80,  82,  84,  86,  88,
		90,  92,  94,  96,  98,
		100, 120, 140, 160, 200
	};

	float binning_mass3[25] =
	{
		40,  50,  60,  70,  80,
		82,  84,  86,  88,  90,
		92,  94,  96,  98,  100,
		105, 110, 115, 120, 130,
		140, 155, 175, 200, 250
	};

	// * Create histogram with name and binning
	hist_pT_lep1       = new TH1D ("hist_pT_lep1",       "",  14, binning_lep1Pt);
	hist_pT_lep2       = new TH1D ("hist_pT_lep2",       "",  14, binning_lep2Pt);
	hist_pT_pho        = new TH1D ("hist_pT_pho",        "",  9,  binning_phoPt);
	hist_pT_jet        = new TH1D ("hist_pT_jet",        "",  9,  binning_jetPt);
	hist_pT_inv        = new TH1D ("hist_pT_inv",        "",  14, binning_invPt);
	hist_eta_lep1      = new TH1D ("hist_eta_lep1",      "",  30, -3, 3);
	hist_eta_lep2      = new TH1D ("hist_eta_lep2",      "",  30, -3, 3);
	hist_eta_pho       = new TH1D ("hist_eta_pho",       "",  30, -3, 3);
	hist_eta_jet       = new TH1D ("hist_eta_jet",       "",  30, -3, 3);
	hist_eta_inv       = new TH1D ("hist_eta_inv",       "",  30, -3, 3);
	hist_phi_lep1      = new TH1D ("hist_phi_lep1",      "",  34, -3.4, 3.4);
	hist_phi_lep2      = new TH1D ("hist_phi_lep2",      "",  34, -3.4, 3.4);
	hist_phi_pho       = new TH1D ("hist_phi_pho",       "",  34, -3.4, 3.4);
	hist_phi_jet       = new TH1D ("hist_phi_jet",       "",  34, -3.4, 3.4);
	hist_phi_inv       = new TH1D ("hist_phi_inv",       "",  34, -3.4, 3.4);
	hist_mass_dilep    = new TH1D ("hist_mass_dilep",    "",  24, binning_mass2);
	hist_mass_dileppho = new TH1D ("hist_mass_dileppho", "",  24, binning_mass3);
	hist_dr_leplep     = new TH1D ("hist_dr_leplep",     "",  40, 0, 8);
	hist_dr_lep1pho    = new TH1D ("hist_dr_lep1pho",    "",  40, 0, 8);
	hist_dr_lep2pho    = new TH1D ("hist_dr_lep2pho",    "",  40, 0, 8);
	hist_dr_lep1jet    = new TH1D ("hist_dr_lep1jet",    "",  40, 0, 8);
	hist_dr_lep2jet    = new TH1D ("hist_dr_lep2jet",    "",  40, 0, 8);
	hist_dr_phojet     = new TH1D ("hist_dr_phojet",     "",  40, 0, 8);
	hist_chIso_pho     = new TH1D ("hist_chIso_pho",     "",  40, 0, 2.0);
	hist_SCEta_pho     = new TH1D ("hist_SCEta_pho",     "", );
	hist_SCRawE_pho    = new TH1D ("hist_SCRawE_pho",    "",  40, 0, 200);
	hist_R9_pho        = new TH1D ("hist_R9_pho",        "",  30, 0, 1.2);
	hist_etaeta_pho    = new TH1D ("hist_etaeta_pho",    "",  30, 0.00, 0.03);
	hist_etaphi_pho    = new TH1D ("hist_etaphi_pho",    "",  50, 0.00, 0.0001);
	hist_S4_pho        = new TH1D ("hist_S4_pho",        "", );
	hist_wEta_pho      = new TH1D ("hist_wEta_pho  ",    "",  30, 0, 3.0);
	hist_wPhi_pho      = new TH1D ("hist_wPhi_pho  ",    "",  30, 0, 3.0);

	// * Activate error
	hist_pT_lep1       -> Sumw2();
	hist_pT_lep2       -> Sumw2();
	hist_pT_pho        -> Sumw2();
	hist_pT_jet        -> Sumw2();
	hist_pT_inv        -> Sumw2();
	hist_eta_lep1      -> Sumw2();
	hist_eta_lep2      -> Sumw2();
	hist_eta_pho       -> Sumw2();
	hist_eta_jet       -> Sumw2();
	hist_eta_inv       -> Sumw2();
	hist_phi_lep1      -> Sumw2();
	hist_phi_lep2      -> Sumw2();
	hist_phi_pho       -> Sumw2();
	hist_phi_jet       -> Sumw2();
	hist_phi_inv       -> Sumw2();
	hist_mass_dilep    -> Sumw2();
	hist_mass_dileppho -> Sumw2();
	hist_dr_leplep     -> Sumw2();
	hist_dr_lep1pho    -> Sumw2();
	hist_dr_lep2pho    -> Sumw2();
	hist_dr_lep1jet    -> Sumw2();
	hist_dr_lep2jet    -> Sumw2();
	hist_dr_phojet     -> Sumw2();
	hist_chIso_pho     -> Sumw2();
	hist_etaeta_pho    -> Sumw2();
	hist_etaphi_pho    -> Sumw2();
	hist_R9_pho        -> Sumw2();
	hist_SCRawE_pho    -> Sumw2();
	hist_wEta_pho      -> Sumw2();
	hist_wPhi_pho      -> Sumw2();

	// * Set axes' name
	string nameLep[2] = {"e", "#mu"};
	int tlep = leptype - 1;

	hist_pT_lep1       -> GetXaxis() -> SetTitle (Form("p_{T}(%s_{1}) [GeV]", nameLep[tlep].data()));
	hist_pT_lep2       -> GetXaxis() -> SetTitle (Form("p_{T}(%s_{2}) [GeV]", nameLep[tlep].data()));
	hist_pT_pho        -> GetXaxis() -> SetTitle ("p_{T}(#gamma) [GeV]");
	hist_pT_jet        -> GetXaxis() -> SetTitle ("p_{T}(j1) [GeV]");
	hist_pT_inv        -> GetXaxis() -> SetTitle ("p_{T}(miss) [GeV]");
	hist_eta_lep1      -> GetXaxis() -> SetTitle (Form("#eta(%s_{1})", nameLep[tlep].data()));
	hist_eta_lep2      -> GetXaxis() -> SetTitle (Form("#eta(%s_{2})", nameLep[tlep].data()));
	hist_eta_pho       -> GetXaxis() -> SetTitle ("#eta(#gamma)");
	hist_eta_jet       -> GetXaxis() -> SetTitle ("#eta(j1)");
	hist_eta_inv       -> GetXaxis() -> SetTitle ("#eta(miss)");
	hist_phi_lep1      -> GetXaxis() -> SetTitle (Form("#phi(%s_{1})", nameLep[tlep].data()));
	hist_phi_lep2      -> GetXaxis() -> SetTitle (Form("#phi(%s_{2})", nameLep[tlep].data()));
	hist_phi_pho       -> GetXaxis() -> SetTitle ("#phi(#gamma)");
	hist_phi_jet       -> GetXaxis() -> SetTitle ("#phi(j1)");
	hist_phi_inv       -> GetXaxis() -> SetTitle ("#phi(miss)");
	hist_mass_dilep    -> GetXaxis() -> SetTitle (Form("mass(%s,%s) [GeV]", nameLep[tlep].data(), nameLep[tlep].data()));
	hist_mass_dileppho -> GetXaxis() -> SetTitle (Form("mass(%s,%s)#gamma [GeV]", nameLep[tlep].data(), nameLep[tlep].data()));
	hist_dr_leplep     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s,%s)", nameLep[tlep].data(), nameLep[tlep].data()));
	hist_dr_lep1pho    -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{1},#gamma)", nameLep[tlep].data()));
	hist_dr_lep2pho    -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{2},#gamma)", nameLep[tlep].data()));
	hist_dr_lep1jet    -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{1},jet)", nameLep[tlep].data()));
	hist_dr_lep2jet    -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{2},jet)", nameLep[tlep].data()));
	hist_dr_phojet     -> GetXaxis() -> SetTitle (Form("#DeltaR(#gamma,jet)"));
	hist_chIso_pho     -> GetXaxis() -> SetTitle ("Ch.H.Iso [GeV]");
	hist_etaeta_pho    -> GetXaxis() -> SetTitle ("#sigma(#eta,#eta)");
	hist_etaphi_pho    -> GetXaxis() -> SetTitle ("#sigma(#eta,#phi)");
	hist_R9_pho        -> GetXaxis() -> SetTitle ("R9(#gamma)");
	hist_SCRawE_pho    -> GetXaxis() -> SetTitle ("E_{SC,raw}(#gamma)");
	hist_wEta_pho      -> GetXaxis() -> SetTitle ("width_{#gamma}(#eta)");
	hist_wPhi_pho      -> GetXaxis() -> SetTitle ("width_{#gamma}(#phi)");

	hist_pT_lep1       -> GetYaxis() -> SetTitle ("#Event");
	hist_pT_lep2       -> GetYaxis() -> SetTitle ("#Event");
	hist_pT_pho        -> GetYaxis() -> SetTitle ("#Event");
	hist_pT_jet        -> GetYaxis() -> SetTitle ("#Event");
	hist_pT_inv        -> GetYaxis() -> SetTitle ("#Event");
	hist_eta_lep1      -> GetYaxis() -> SetTitle ("#Event");
	hist_eta_lep2      -> GetYaxis() -> SetTitle ("#Event");
	hist_eta_pho       -> GetYaxis() -> SetTitle ("#Event");
	hist_eta_jet       -> GetYaxis() -> SetTitle ("#Event");
	hist_eta_inv       -> GetYaxis() -> SetTitle ("#Event");
	hist_phi_lep1      -> GetYaxis() -> SetTitle ("#Event");
	hist_phi_lep2      -> GetYaxis() -> SetTitle ("#Event");
	hist_phi_pho       -> GetYaxis() -> SetTitle ("#Event");
	hist_phi_jet       -> GetYaxis() -> SetTitle ("#Event");
	hist_phi_inv       -> GetYaxis() -> SetTitle ("#Event");
	hist_mass_dilep    -> GetYaxis() -> SetTitle ("#Event");
	hist_mass_dileppho -> GetYaxis() -> SetTitle ("#Event");
	hist_dr_leplep     -> GetYaxis() -> SetTitle ("#Event");
	hist_dr_lep1pho    -> GetYaxis() -> SetTitle ("#Event");
	hist_dr_lep2pho    -> GetYaxis() -> SetTitle ("#Event");
	hist_dr_lep1jet    -> GetYaxis() -> SetTitle ("#Event");
	hist_dr_lep2jet    -> GetYaxis() -> SetTitle ("#Event");
	hist_dr_phojet     -> GetYaxis() -> SetTitle ("#Event");
	hist_chIso_pho     -> GetYaxis() -> SetTitle ("#Event");
	hist_etaeta_pho    -> GetYaxis() -> SetTitle ("#Event");
	hist_etaphi_pho    -> GetYaxis() -> SetTitle ("#Event");
	hist_R9_pho        -> GetYaxis() -> SetTitle ("#Event");
	hist_SCRawE_pho    -> GetYaxis() -> SetTitle ("#Event");
	hist_wEta_pho      -> GetYaxis() -> SetTitle ("#Event");
	hist_wPhi_pho      -> GetYaxis() -> SetTitle ("#Event");
}


void FillHistogram (TreeReader &tree_input, int leptype, tuple<int,int,int,int> objID, double scale, float puwei, float genwei)
{
	int ilep1 = get<0> (objID);
	int ilep2 = get<1> (objID);
	int ipho  = get<2> (objID);
	int ijet  = get<3> (objID);

	if (ilep1 == ilep2)   printf ("  |   |-- Error: fuck, lep1 = lep2 = %d!!!\n", ilep1);


	// + List of input
	//----------------
	// * Lepctron
	int    nLep;
	float *lepPt;
	float *lepEta;
	float *lepPhi;
	float *lepEn;

	if (leptype == 1)
	{
		nLep    = tree_input . GetInt      ("nEle");
		lepPt   = tree_input . GetPtrFloat ("eleCalibPt");
		lepEta  = tree_input . GetPtrFloat ("eleEta");
		lepPhi  = tree_input . GetPtrFloat ("elePhi");
		lepEn   = tree_input . GetPtrFloat ("eleCalibEn");
	}
	else
	{
		nLep    = tree_input . GetInt      ("nMu");
		lepPt   = tree_input . GetPtrFloat ("muCorPt");
		lepEta  = tree_input . GetPtrFloat ("muEta");
		lepPhi  = tree_input . GetPtrFloat ("muPhi");
		lepEn   = tree_input . GetPtrFloat ("muEn");
	}

	// * Photon
	int    nPho                 = tree_input . GetInt      ("nPho");
	float *phoCalibEt           = tree_input . GetPtrFloat ("phoCalibEt");
	float *phoEta               = tree_input . GetPtrFloat ("phoEta");
	float *phoPhi               = tree_input . GetPtrFloat ("phoPhi");
	float *phoE                 = tree_input . GetPtrFloat ("phoE");
	float *phoPFChIso           = tree_input . GetPtrFloat ("phoPFChIso");
	float *phoPFPhoIso          = tree_input . GetPtrFloat ("phoPFPhoIso");
	float *phoSCEta             = tree_input . GetPtrFloat ("phoSCEta");
	float *phoSCRawE            = tree_input . GetPtrFloat ("phoSCRawE");
	float *phoR9                = tree_input . GetPtrFloat ("phoR9");
	float *phoSigmaIEtaIEtaFull = tree_input . GetPtrFloat ("phoSigmaIEtaIEtaFull");
	float *phoSigmaIEtaIPhiFull = tree_input . GetPtrFloat ("phoSigmaIEtaIPhiFull");
	float *phoE2x2Full          = tree_input . GetPtrFloat ("phoE2x2Full");
	float *phoE5x5Full          = tree_input . GetPtrFloat ("phoE5x5Full");
	float *phoSCEtaWidth        = tree_input . GetPtrFloat ("phoSCEtaWidth");
	float *phoSCPhiWidth        = tree_input . GetPtrFloat ("phoSCPhiWidth");
	float *phoESEffSigmaRR      = tree_input . GetPtrFloat ("phoESEffSigmaRR");
	float *phoESEnP1            = tree_input . GetPtrFloat ("phoESEnP1");
	float *phoESEnP2            = tree_input . GetPtrFloat ("phoESEnP2");

	// * Jet
	int    nJet       = tree_input . GetInt      ("nJet");
	float *jetPt      = tree_input . GetPtrFloat ("jetPt");
	float *jetEta     = tree_input . GetPtrFloat ("jetEta");
	float *jetPhi     = tree_input . GetPtrFloat ("jetPhi");
	float *jetEn      = tree_input . GetPtrFloat ("jetEn");
	float *jetP4Smear = tree_input . GetPtrFloat ("jetP4Smear");

	// * Missing ET
	float pfMET    = tree_input . GetFloat ("pfXYCorMET");
	float pfMETPhi = tree_input . GetFloat ("pfXYCorMETPhi");


	// + List of output variables
	//---------------------------
	TLorentzVector v4d_lep1;
	TLorentzVector v4d_lep2;
	TLorentzVector v4d_pho;
	TLorentzVector v4d_diobj;
	TLorentzVector v4d_triobj;

	float ptLep1     = lepPt[ilep1];
	float ptLep2     = lepPt[ilep2];
	float ptPho      = phoCalibEt[ipho];
	float ptJet      = (ijet>-1) ? jetPt[ijet] : -1;
	float ptInv      = pfMET;
	float etaLep1    = lepEta[ilep1];
	float etaLep2    = lepEta[ilep2];
	float etaPho     = phoEta[ipho];
	float etaJet     = (ijet>-1) ? jetEta[ijet] : 50;
	float etaInv     = 0;
	float phiLep1    = lepPhi[ilep1];
	float phiLep2    = lepPhi[ilep2];
	float phiPho     = phoPhi[ipho];
	float phiJet     = (ijet>-1) ? jetPhi[ijet] : 50;
	float phiInv     = pfMETPhi;
	float massDiobj  = 0;
	float massTriobj = 0;
	float drleplep   = compute_DeltaR (etaLep1, etaLep2, phiLep1, phiLep2);
	float drlep1pho  = compute_DeltaR (etaLep1, etaPho,  phiLep1, phiPho);
	float drlep2pho  = compute_DeltaR (etaLep2, etaPho,  phiLep2, phiPho);
	float drlep1jet  = compute_DeltaR (etaLep1, etaJet,  phiLep1, phiJet);
	float drlep2jet  = compute_DeltaR (etaLep2, etaJet,  phiLep2, phiJet);
	float drphojet   = compute_DeltaR (etaPho,  etaJet,  phiPho,  phiJet);
	float chIso      = phoPFChIso[ipho];
	float sigetaeta  = phoSigmaIEtaIEtaFull[ipho];
	float sigetaphi  = phoSigmaIEtaIPhiFull[ipho];
	float r9         = phoR9[ipho];
	float scRawEn    = phoSCRawE[ipho];
	float wEta       = phoSCEtaWidth[ipho];
	float wPhi       = phoSCPhiWidth[ipho];

	float enLep1 = lepEn[ilep1];
	float enLep2 = lepEn[ilep2];
	v4d_lep1 . SetPtEtaPhiE (ptLep1, etaLep1, phiLep1, enLep1);
	v4d_lep2 . SetPtEtaPhiE (ptLep2, etaLep2, phiLep2, enLep2);
	v4d_pho  . SetPtEtaPhiM (ptPho,  etaPho,  phiPho,  0);
	v4d_diobj = v4d_lep1 + v4d_lep2;
	v4d_triobj = v4d_diobj + v4d_pho;

	massDiobj  = v4d_diobj . M();
	massTriobj = v4d_triobj . M();

	hist_pT_lep1       -> Fill (ptLep1,     puwei*genwei*scale);
	hist_pT_lep2       -> Fill (ptLep2,     puwei*genwei*scale);
	hist_pT_pho        -> Fill (ptPho,      puwei*genwei*scale);
	hist_pT_inv        -> Fill (ptInv,      puwei*genwei*scale);
	hist_eta_lep1      -> Fill (etaLep1,    puwei*genwei*scale);
	hist_eta_lep2      -> Fill (etaLep2,    puwei*genwei*scale);
	hist_eta_pho       -> Fill (etaPho,     puwei*genwei*scale);
	hist_eta_inv       -> Fill (etaInv,     puwei*genwei*scale);
	hist_phi_lep1      -> Fill (phiLep1,    puwei*genwei*scale);
	hist_phi_lep2      -> Fill (phiLep2,    puwei*genwei*scale);
	hist_phi_pho       -> Fill (phiPho,     puwei*genwei*scale);
	hist_phi_inv       -> Fill (phiInv,     puwei*genwei*scale);
	hist_mass_dilep    -> Fill (massDiobj,  puwei*genwei*scale);
	hist_mass_dileppho -> Fill (massTriobj, puwei*genwei*scale);
	hist_dr_leplep     -> Fill (drleplep,   puwei*genwei*scale);
	hist_dr_lep1pho    -> Fill (drlep1pho,  puwei*genwei*scale);
	hist_dr_lep2pho    -> Fill (drlep2pho,  puwei*genwei*scale);
	hist_chIso_pho     -> Fill (chIso,      puwei*genwei*scale);
	hist_etaeta_pho    -> Fill (sigetaeta,  puwei*genwei*scale);
	hist_etaphi_pho    -> Fill (sigetaphi,  puwei*genwei*scale);
	hist_R9_pho        -> Fill (r9,         puwei*genwei*scale);
	hist_SCRawE_pho    -> Fill (scRawEn,    puwei*genwei*scale);
	hist_wEta_pho      -> Fill (wEta,       puwei*genwei*scale);
	hist_wPhi_pho      -> Fill (wPhi,       puwei*genwei*scale);

	if (ijet >-1)
	{
		hist_pT_jet        -> Fill (ptJet,      puwei*genwei*scale);
		hist_eta_jet       -> Fill (etaJet,     puwei*genwei*scale);
		hist_phi_jet       -> Fill (phiJet,     puwei*genwei*scale);
		hist_dr_lep1jet    -> Fill (drlep1jet,  puwei*genwei*scale);
		hist_dr_lep2jet    -> Fill (drlep2jet,  puwei*genwei*scale);
		hist_dr_phojet     -> Fill (drphojet,   puwei*genwei*scale);
	}

	//hist_pT_jet        -> Fill (ptJet,      puwei*genwei*scale);
	//hist_eta_jet       -> Fill (etaJet,     puwei*genwei*scale);
	//hist_phi_jet       -> Fill (phiJet,     puwei*genwei*scale);
	//hist_dr_lep1jet    -> Fill (drlep1jet,  puwei*genwei*scale);
	//hist_dr_lep2jet    -> Fill (drlep2jet,  puwei*genwei*scale);
	//hist_dr_phojet     -> Fill (drphojet,   puwei*genwei*scale);
}


void  WriteHistogram ()
{
	hist_pT_lep1       -> Write ();
	hist_pT_lep2       -> Write ();
	hist_pT_pho        -> Write ();
	hist_pT_jet        -> Write ();
	hist_pT_inv        -> Write ();
	hist_eta_lep1      -> Write ();
	hist_eta_lep2      -> Write ();
	hist_eta_pho       -> Write ();
	hist_eta_jet       -> Write ();
	hist_eta_inv       -> Write ();
	hist_phi_lep1      -> Write ();
	hist_phi_lep2      -> Write ();
	hist_phi_pho       -> Write ();
	hist_phi_jet       -> Write ();
	hist_phi_inv       -> Write ();
	hist_mass_dilep    -> Write ();
	hist_mass_dileppho -> Write ();
	hist_dr_leplep     -> Write ();
	hist_dr_lep1pho    -> Write ();
	hist_dr_lep2pho    -> Write ();
	hist_dr_lep1jet    -> Write ();
	hist_dr_lep2jet    -> Write ();
	hist_dr_phojet     -> Write ();
	hist_chIso_pho     -> Write ();
	hist_etaeta_pho    -> Write ();
	hist_etaphi_pho    -> Write ();
	hist_R9_pho        -> Write ();
	hist_SCRawE_pho    -> Write ();
	hist_wEta_pho      -> Write ();
	hist_wPhi_pho      -> Write ();
}


void CleanHistogram ()
{
	delete hist_pT_lep1;
	delete hist_pT_lep2;
	delete hist_pT_pho;
	delete hist_pT_jet;
	delete hist_pT_inv;
	delete hist_eta_lep1;
	delete hist_eta_lep2;
	delete hist_eta_pho;
	delete hist_eta_jet;
	delete hist_eta_inv;
	delete hist_phi_lep1;
	delete hist_phi_lep2;
	delete hist_phi_pho;
	delete hist_phi_jet;
	delete hist_phi_inv;
	delete hist_mass_dilep;
	delete hist_mass_dileppho;
	delete hist_dr_leplep;
	delete hist_dr_lep1pho;
	delete hist_dr_lep2pho;
	delete hist_dr_lep1jet;
	delete hist_dr_lep2jet;
	delete hist_dr_phojet;
	delete hist_chIso_pho;
	delete hist_etaeta_pho;
	delete hist_etaphi_pho;
	delete hist_R9_pho;
	delete hist_SCRawE_pho;
	delete hist_wEta_pho;
	delete hist_wPhi_pho;
}

#endif
