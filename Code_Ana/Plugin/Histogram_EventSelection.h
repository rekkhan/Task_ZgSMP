#ifndef HISTOGRAM_EVENTSELECTION_H
#define HISTOGRAM_EVENTSELECTION_H


#include "../Utility/untuplizer_v09.h"
#include "../Utility/Calculator.h"
#include "TLorentzVector.h"

// + List of histogram
//--------------------
// * Tranverse momentum
TH1D *histEE_pT_lep1;
TH1D *histEE_pT_lep2;
TH1D *histEE_pT_pho;
TH1D *histEE_pT_jet;
TH1D *histEE_pT_inv;

TH1D *histEB_pT_lep1;
TH1D *histEB_pT_lep2;
TH1D *histEB_pT_pho;
TH1D *histEB_pT_jet;
TH1D *histEB_pT_inv;

// * Pseudorapidity
TH1D *histEE_eta_lep1;
TH1D *histEE_eta_lep2;
TH1D *histEE_eta_pho;
TH1D *histEE_eta_jet;
TH1D *histEE_eta_inv;

TH1D *histEB_eta_lep1;
TH1D *histEB_eta_lep2;
TH1D *histEB_eta_pho;
TH1D *histEB_eta_jet;
TH1D *histEB_eta_inv;

// * Azimuthal angle
TH1D *histEE_phi_lep1;
TH1D *histEE_phi_lep2;
TH1D *histEE_phi_pho;
TH1D *histEE_phi_jet;
TH1D *histEE_phi_inv;

TH1D *histEB_phi_lep1;
TH1D *histEB_phi_lep2;
TH1D *histEB_phi_pho;
TH1D *histEB_phi_jet;
TH1D *histEB_phi_inv;

// * Mass
TH1D *histEE_mass_2body;
TH1D *histEE_mass_3body;

TH1D *histEB_mass_2body;
TH1D *histEB_mass_3body;

// * Pseudorapidity separation
TH1D *histEE_dr_lep1pho;
TH1D *histEE_dr_lep2pho;
TH1D *histEE_dr_lep1jet;
TH1D *histEE_dr_lep2jet;
TH1D *histEE_dr_leplep;
TH1D *histEE_dr_phojet;

TH1D *histEB_dr_lep1pho;
TH1D *histEB_dr_lep2pho;
TH1D *histEB_dr_lep1jet;
TH1D *histEB_dr_lep2jet;
TH1D *histEB_dr_leplep;
TH1D *histEB_dr_phojet;

// * Angular separation
TH1D *histEE_dphi_lep1inv;
TH1D *histEE_dphi_lep2inv;
TH1D *histEE_dphi_phoinv;
TH1D *histEE_dphi_jetinv;

TH1D *histEB_dphi_lep1inv;
TH1D *histEB_dphi_lep2inv;
TH1D *histEB_dphi_phoinv;
TH1D *histEB_dphi_jetinv;

// * Shower shape variables
TH1D *histEE_chIso_pho;
TH1D *histEE_sceta_pho;
TH1D *histEE_scEn_pho;
TH1D *histEE_r9_pho;
TH1D *histEE_sigetaeta_pho;
TH1D *histEE_sigetaphi_pho;
TH1D *histEE_s4_pho;
TH1D *histEE_etawidth_pho;
TH1D *histEE_phiwidth_pho;
TH1D *histEE_esSigRR_pho;
TH1D *histEE_ESoverSC_pho;

TH1D *histEB_chIso_pho;
TH1D *histEB_sceta_pho;
TH1D *histEB_scEn_pho;
TH1D *histEB_r9_pho;
TH1D *histEB_sigetaeta_pho;
TH1D *histEB_sigetaphi_pho;
TH1D *histEB_s4_pho;
TH1D *histEB_etawidth_pho;
TH1D *histEB_phiwidth_pho;



void InitHistogram (int leptype)
{
	// + Histogram binning
	//--------------------
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



	// + Create histogram with name and binning
	//-----------------------------------------
	// * Tranverse momentum
	histEE_pT_lep1       = new TH1D ("histEE_pT_lep1",        "", 14, binning_lep1Pt);
	histEE_pT_lep2       = new TH1D ("histEE_pT_lep2",        "", 14, binning_lep2Pt);
	histEE_pT_pho        = new TH1D ("histEE_pT_pho",         "", 9,  binning_phoPt );
	histEE_pT_jet        = new TH1D ("histEE_pT_jet",         "", 9,  binning_jetPt);
	histEE_pT_inv        = new TH1D ("histEE_pT_inv",         "", 14, binning_invPt);

	histEB_pT_lep1       = new TH1D ("histEB_pT_lep1",        "", 14, binning_lep1Pt);
	histEB_pT_lep2       = new TH1D ("histEB_pT_lep2",        "", 14, binning_lep2Pt);
	histEB_pT_pho        = new TH1D ("histEB_pT_pho",         "", 9,  binning_phoPt );
	histEB_pT_jet        = new TH1D ("histEB_pT_jet",         "", 9,  binning_jetPt);
	histEB_pT_inv        = new TH1D ("histEB_pT_inv",         "", 14, binning_invPt);

	// * Pseudorapidity
	histEE_eta_lep1      = new TH1D ("histEE_eta_lep1",       "", 30, -3.0, 3.0);
	histEE_eta_lep2      = new TH1D ("histEE_eta_lep2",       "", 30, -3.0, 3.0);
	histEE_eta_pho       = new TH1D ("histEE_eta_pho",        "", 30, -3.0, 3.0);
	histEE_eta_jet       = new TH1D ("histEE_eta_jet",        "", 30, -3.0, 3.0);
	histEE_eta_inv       = new TH1D ("histEE_eta_inv",        "", 30, -3.0, 3.0);

	histEB_eta_lep1      = new TH1D ("histEB_eta_lep1",       "", 30, -3.0, 3.0);
	histEB_eta_lep2      = new TH1D ("histEB_eta_lep2",       "", 30, -3.0, 3.0);
	histEB_eta_pho       = new TH1D ("histEB_eta_pho",        "", 30, -3.0, 3.0);
	histEB_eta_jet       = new TH1D ("histEB_eta_jet",        "", 30, -3.0, 3.0);
	histEB_eta_inv       = new TH1D ("histEB_eta_inv",        "", 30, -3.0, 3.0);

	// * Azimuthal angle
	histEE_phi_lep1      = new TH1D ("histEE_phi_lep1",       "", 34, -3.4, 3.4);
	histEE_phi_lep2      = new TH1D ("histEE_phi_lep2",       "", 34, -3.4, 3.4);
	histEE_phi_pho       = new TH1D ("histEE_phi_pho",        "", 34, -3.4, 3.4);
	histEE_phi_jet       = new TH1D ("histEE_phi_jet",        "", 34, -3.4, 3.4);
	histEE_phi_inv       = new TH1D ("histEE_phi_inv",        "", 34, -3.4, 3.4);

	histEB_phi_lep1      = new TH1D ("histEB_phi_lep1",       "", 34, -3.4, 3.4);
	histEB_phi_lep2      = new TH1D ("histEB_phi_lep2",       "", 34, -3.4, 3.4);
	histEB_phi_pho       = new TH1D ("histEB_phi_pho",        "", 34, -3.4, 3.4);
	histEB_phi_jet       = new TH1D ("histEB_phi_jet",        "", 34, -3.4, 3.4);
	histEB_phi_inv       = new TH1D ("histEB_phi_inv",        "", 34, -3.4, 3.4);

	// * Mass
	histEE_mass_2body    = new TH1D ("histEE_mass_2body",     "", 24, binning_mass2);
	histEE_mass_3body    = new TH1D ("histEE_mass_3body",     "", 23, binning_mass3);

	histEB_mass_2body    = new TH1D ("histEB_mass_2body",     "", 24, binning_mass2);
	histEB_mass_3body    = new TH1D ("histEB_mass_3body",     "", 23, binning_mass3);

	// * Pseudorapidity separation
	histEE_dr_lep1pho    = new TH1D ("histEE_dr_lep1pho",     "", 40, 0, 8);
	histEE_dr_lep2pho    = new TH1D ("histEE_dr_lep2pho",     "", 40, 0, 8);
	histEE_dr_lep1jet    = new TH1D ("histEE_dr_lep1jet",     "", 40, 0, 8);
	histEE_dr_lep2jet    = new TH1D ("histEE_dr_lep2jet",     "", 40, 0, 8);
	histEE_dr_leplep     = new TH1D ("histEE_dr_leplep",      "", 40, 0, 8);
	histEE_dr_phojet     = new TH1D ("histEE_dr_phojet",      "", 40, 0, 8);

	histEB_dr_lep1pho    = new TH1D ("histEB_dr_lep1pho",     "", 40, 0, 8);
	histEB_dr_lep2pho    = new TH1D ("histEB_dr_lep2pho",     "", 40, 0, 8);
	histEB_dr_lep1jet    = new TH1D ("histEB_dr_lep1jet",     "", 40, 0, 8);
	histEB_dr_lep2jet    = new TH1D ("histEB_dr_lep2jet",     "", 40, 0, 8);
	histEB_dr_leplep     = new TH1D ("histEB_dr_leplep",      "", 40, 0, 8);
	histEB_dr_phojet     = new TH1D ("histEB_dr_phojet",      "", 40, 0, 8);

	// * Angular separation
	histEE_dphi_lep1inv  = new TH1D ("histEE_dphi_lep1inv",   "", 18, 0, 3.6);
	histEE_dphi_lep2inv  = new TH1D ("histEE_dphi_lep2inv",   "", 18, 0, 3.6);
	histEE_dphi_phoinv   = new TH1D ("histEE_dphi_phoinv",    "", 18, 0, 3.6);
	histEE_dphi_jetinv   = new TH1D ("histEE_dphi_jetinv",    "", 18, 0, 3.6);

	histEB_dphi_lep1inv  = new TH1D ("histEB_dphi_lep1inv",   "", 18, 0, 3.6);
	histEB_dphi_lep2inv  = new TH1D ("histEB_dphi_lep2inv",   "", 18, 0, 3.6);
	histEB_dphi_phoinv   = new TH1D ("histEB_dphi_phoinv",    "", 18, 0, 3.6);
	histEB_dphi_jetinv   = new TH1D ("histEB_dphi_jetinv",    "", 18, 0, 3.6);

	// * Shower shape variables
	histEE_chIso_pho     = new TH1D ("histEE_chIso_pho",      "", 160, 0, 16);
	histEE_sceta_pho     = new TH1D ("histEE_sceta_pho",      "", 20, 0, 4.0);
	histEE_scEn_pho      = new TH1D ("histEE_scEn_pho",       "", 20, 0, 400);
	histEE_r9_pho        = new TH1D ("histEE_r9_pho",         "", 30, 0, 1.2);
	histEE_sigetaeta_pho = new TH1D ("histEE_sigetaeta_pho",  "", 30, 0, 0.03);
	histEE_sigetaphi_pho = new TH1D ("histEE_sigetaphi_pho",  "", 25, 0, 0.0001);
	histEE_s4_pho        = new TH1D ("histEE_s4_pho",         "", 20, 0, 1.0);
	histEE_etawidth_pho  = new TH1D ("histEE_etawidth_pho",   "", 20, 0, 0.1);
	histEE_phiwidth_pho  = new TH1D ("histEE_phiwidth_pho",   "", 20, 0, 0.1);
	histEE_esSigRR_pho   = new TH1D ("histEE_esSigRR_pho",    "", 15, 0, 15);
	histEE_ESoverSC_pho  = new TH1D ("histEE_ESoverSC_pho",   "", 20, 0, 0.04);

	histEB_chIso_pho     = new TH1D ("histEB_chIso_pho",      "", 160, 0, 16);
	histEB_sceta_pho     = new TH1D ("histEB_sceta_pho",      "", 20, 0, 4.0);
	histEB_scEn_pho      = new TH1D ("histEB_scEn_pho",       "", 20, 0, 400);
	histEB_r9_pho        = new TH1D ("histEB_r9_pho",         "", 30, 0, 1.2);
	histEB_sigetaeta_pho = new TH1D ("histEB_sigetaeta_pho",  "", 30, 0, 0.03);
	histEB_sigetaphi_pho = new TH1D ("histEB_sigetaphi_pho",  "", 25, 0, 0.0001);
	histEB_s4_pho        = new TH1D ("histEB_s4_pho",         "", 20, 0, 1.0);
	histEB_etawidth_pho  = new TH1D ("histEB_etawidth_pho",   "", 20, 0, 0.1);
	histEB_phiwidth_pho  = new TH1D ("histEB_phiwidth_pho",   "", 20, 0, 0.1);



	// + Set Sumw2 (uncertainty)
	//--------------------------
	// * Tranverse momentum
	histEE_pT_lep1       -> Sumw2();
	histEE_pT_lep2       -> Sumw2();
	histEE_pT_pho        -> Sumw2();
	histEE_pT_jet        -> Sumw2();
	histEE_pT_inv        -> Sumw2();

	histEB_pT_lep1       -> Sumw2();
	histEB_pT_lep2       -> Sumw2();
	histEB_pT_pho        -> Sumw2();
	histEB_pT_jet        -> Sumw2();
	histEB_pT_inv        -> Sumw2();

	// * Pseudorapidity
	histEE_eta_lep1      -> Sumw2();
	histEE_eta_lep2      -> Sumw2();
	histEE_eta_pho       -> Sumw2();
	histEE_eta_jet       -> Sumw2();
	histEE_eta_inv       -> Sumw2();

	histEB_eta_lep1      -> Sumw2();
	histEB_eta_lep2      -> Sumw2();
	histEB_eta_pho       -> Sumw2();
	histEB_eta_jet       -> Sumw2();
	histEB_eta_inv       -> Sumw2();

	// * Azimuthal angle
	histEE_phi_lep1      -> Sumw2();
	histEE_phi_lep2      -> Sumw2();
	histEE_phi_pho       -> Sumw2();
	histEE_phi_jet       -> Sumw2();
	histEE_phi_inv       -> Sumw2();

	histEB_phi_lep1      -> Sumw2();
	histEB_phi_lep2      -> Sumw2();
	histEB_phi_pho       -> Sumw2();
	histEB_phi_jet       -> Sumw2();
	histEB_phi_inv       -> Sumw2();

	// * Mass
	histEE_mass_2body    -> Sumw2();
	histEE_mass_3body    -> Sumw2();

	histEB_mass_2body    -> Sumw2();
	histEB_mass_3body    -> Sumw2();

	// * Pseudorapidity separation
	histEE_dr_lep1pho    -> Sumw2();
	histEE_dr_lep2pho    -> Sumw2();
	histEE_dr_lep1jet    -> Sumw2();
	histEE_dr_lep2jet    -> Sumw2();
	histEE_dr_leplep     -> Sumw2();
	histEE_dr_phojet     -> Sumw2();

	histEB_dr_lep1pho    -> Sumw2();
	histEB_dr_lep2pho    -> Sumw2();
	histEB_dr_lep1jet    -> Sumw2();
	histEB_dr_lep2jet    -> Sumw2();
	histEB_dr_leplep     -> Sumw2();
	histEB_dr_phojet     -> Sumw2();

	// * Angular separation
	histEE_dphi_lep1inv  -> Sumw2();
	histEE_dphi_lep2inv  -> Sumw2();
	histEE_dphi_phoinv   -> Sumw2();
	histEE_dphi_jetinv   -> Sumw2();

	histEB_dphi_lep1inv  -> Sumw2();
	histEB_dphi_lep2inv  -> Sumw2();
	histEB_dphi_phoinv   -> Sumw2();
	histEB_dphi_jetinv   -> Sumw2();

	// * Shower shape variables
	histEE_chIso_pho     -> Sumw2();
	histEE_sceta_pho     -> Sumw2();
	histEE_scEn_pho      -> Sumw2();
	histEE_r9_pho        -> Sumw2();
	histEE_sigetaeta_pho -> Sumw2();
	histEE_sigetaphi_pho -> Sumw2();
	histEE_s4_pho        -> Sumw2();
	histEE_etawidth_pho  -> Sumw2();
	histEE_phiwidth_pho  -> Sumw2();
	histEE_esSigRR_pho   -> Sumw2();
	histEE_ESoverSC_pho  -> Sumw2();

	histEB_chIso_pho     -> Sumw2();
	histEB_sceta_pho     -> Sumw2();
	histEB_scEn_pho      -> Sumw2();
	histEB_r9_pho        -> Sumw2();
	histEB_sigetaeta_pho -> Sumw2();
	histEB_sigetaphi_pho -> Sumw2();
	histEB_s4_pho        -> Sumw2();
	histEB_etawidth_pho  -> Sumw2();
	histEB_phiwidth_pho  -> Sumw2();



	// + Set axes' name
	//-----------------
	string tlep[2] = {"e", "#mu"};
	int t = leptype - 1;

	// * Tranverse momentum
	histEE_pT_lep1        -> GetXaxis() -> SetTitle (Form("p_{T}(%s_{1}) [GeV] (EE)", tlep[t].data()));
	histEE_pT_lep2        -> GetXaxis() -> SetTitle (Form("p_{T}(%s_{1}) [GeV] (EE)", tlep[t].data()));
	histEE_pT_pho         -> GetXaxis() -> SetTitle (Form("E_{T}(#gamma) [GeV] (EE)"));
	histEE_pT_jet         -> GetXaxis() -> SetTitle (Form("p_{T}(j) [GeV] (EE)"));
	histEE_pT_inv         -> GetXaxis() -> SetTitle (Form("p_{T}(miss) [GeV] (EE)"));

	histEB_pT_lep1        -> GetXaxis() -> SetTitle (Form("p_{T}(%s_{1}) [GeV] (EB)", tlep[t].data()));
	histEB_pT_lep2        -> GetXaxis() -> SetTitle (Form("p_{T}(%s_{1}) [GeV] (EB)", tlep[t].data()));
	histEB_pT_pho         -> GetXaxis() -> SetTitle (Form("E_{T}(#gamma) [GeV] (EB)"));
	histEB_pT_jet         -> GetXaxis() -> SetTitle (Form("p_{T}(j) [GeV] (EB)"));
	histEB_pT_inv         -> GetXaxis() -> SetTitle (Form("p_{T}(miss) [GeV] (EB)"));

	// * Pseudorapidity
	histEE_eta_lep1       -> GetXaxis() -> SetTitle (Form("#eta(%s_{1}) (EE)", tlep[t].data()));
	histEE_eta_lep2       -> GetXaxis() -> SetTitle (Form("#eta(%s_{2}) (EE)", tlep[t].data()));
	histEE_eta_pho        -> GetXaxis() -> SetTitle (Form("#eta(#gamma) (EE)"));
	histEE_eta_jet        -> GetXaxis() -> SetTitle (Form("#eta(j) (EE)"));
	histEE_eta_inv        -> GetXaxis() -> SetTitle (Form("#eta(#slash{E_T}) (EE)"));

	histEB_eta_lep1       -> GetXaxis() -> SetTitle (Form("#eta(%s_{1}) (EB)", tlep[t].data()));
	histEB_eta_lep2       -> GetXaxis() -> SetTitle (Form("#eta(%s_{2}) (EB)", tlep[t].data()));
	histEB_eta_pho        -> GetXaxis() -> SetTitle (Form("#eta(#gamma) (EB)"));
	histEB_eta_jet        -> GetXaxis() -> SetTitle (Form("#eta(j) (EB)"));
	histEB_eta_inv        -> GetXaxis() -> SetTitle (Form("#eta(#slash{E_T}f) (EB)"));

	// * Azimuthal angle
	histEE_phi_lep1       -> GetXaxis() -> SetTitle (Form("#phi(%s_{1}) [rad] (EE)", tlep[t].data()));
	histEE_phi_lep2       -> GetXaxis() -> SetTitle (Form("#phi(%s_{2}) [rad] (EE)", tlep[t].data()));
	histEE_phi_pho        -> GetXaxis() -> SetTitle (Form("#phi(#gamma) [rad] (EE)"));
	histEE_phi_jet        -> GetXaxis() -> SetTitle (Form("#phi(j) [rad] (EE)"));
	histEE_phi_inv        -> GetXaxis() -> SetTitle (Form("#phi(#slash{E_T}) [rad] (EE)"));

	histEB_phi_lep1       -> GetXaxis() -> SetTitle (Form("#phi(%s_{1}) [rad] (EB)", tlep[t].data()));
	histEB_phi_lep2       -> GetXaxis() -> SetTitle (Form("#phi(%s_{2}) [rad] (EB)", tlep[t].data()));
	histEB_phi_pho        -> GetXaxis() -> SetTitle (Form("#phi(#gamma) [rad] (EB)"));
	histEB_phi_jet        -> GetXaxis() -> SetTitle (Form("#phi(j) [rad] (EB)"));
	histEB_phi_inv        -> GetXaxis() -> SetTitle (Form("#phi(#slash{E_T}) [rad] (EB)"));

	// * Mass
	histEE_mass_2body     -> GetXaxis() -> SetTitle (Form("mass(%s%s) [GeV] (EE)", tlep[t].data(), tlep[t].data()));
	histEE_mass_3body     -> GetXaxis() -> SetTitle (Form("mass(%s%s#gamma) [GeV] (EE)", tlep[t].data(), tlep[t].data()));

	histEB_mass_2body     -> GetXaxis() -> SetTitle (Form("mass(%s%s) [GeV] (EB)", tlep[t].data(), tlep[t].data()));
	histEB_mass_3body     -> GetXaxis() -> SetTitle (Form("mass(%s%s#gamma) [GeV] (EB)", tlep[t].data(), tlep[t].data()));

	// * Pseudorapidity separation
	histEE_dr_lep1pho     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{1},#gamma) (EE)", tlep[t].data()));
	histEE_dr_lep2pho     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{2},#gamma) (EE)", tlep[t].data()));
	histEE_dr_lep1jet     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{1},j) (EE)", tlep[t].data()));
	histEE_dr_lep2jet     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{2},j) (EE)", tlep[t].data()));
	histEE_dr_leplep      -> GetXaxis() -> SetTitle (Form("#DeltaR(%s,%s) (EE)", tlep[t].data(), tlep[t].data()));
	histEE_dr_phojet      -> GetXaxis() -> SetTitle (Form("#DeltaR(#gamma,j) (EE)"));

	histEB_dr_lep1pho     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{1},#gamma) (EB)", tlep[t].data()));
	histEB_dr_lep2pho     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{2},#gamma) (EB)", tlep[t].data()));
	histEB_dr_lep1jet     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{1},j) (EB)", tlep[t].data()));
	histEB_dr_lep2jet     -> GetXaxis() -> SetTitle (Form("#DeltaR(%s_{2},j) (EB)", tlep[t].data()));
	histEB_dr_leplep      -> GetXaxis() -> SetTitle (Form("#DeltaR(%s,%s) (EB)", tlep[t].data(), tlep[t].data()));
	histEB_dr_phojet      -> GetXaxis() -> SetTitle (Form("#DeltaR(#gamma,j) (EB)"));

	// * Angular separation
	histEE_dphi_lep1inv   -> GetXaxis() -> SetTitle (Form("#Delta#phi(%s_{1},#slash{E_T}) [rad] (EE)", tlep[t].data()));
	histEE_dphi_lep2inv   -> GetXaxis() -> SetTitle (Form("#Delta#phi(%s_{2},#slash{E_T}) [rad] (EE)", tlep[t].data()));
	histEE_dphi_phoinv    -> GetXaxis() -> SetTitle (Form("#Delta#phi(#gamma,#slash{E_T}) [rad] (EE)"));
	histEE_dphi_jetinv    -> GetXaxis() -> SetTitle (Form("#Delta#phi(j,#slash{E_T}) [rad] (EE)"));

	histEB_dphi_lep1inv   -> GetXaxis() -> SetTitle (Form("#Delta#phi(%s_{1},#slash{E_T}) [rad] (EB)", tlep[t].data()));
	histEB_dphi_lep2inv   -> GetXaxis() -> SetTitle (Form("#Delta#phi(%s_{2},#slash{E_T}) [rad] (EB)", tlep[t].data()));
	histEB_dphi_phoinv    -> GetXaxis() -> SetTitle (Form("#Delta#phi(#gamma,#slash{E_T}) [rad] (EB)"));
	histEB_dphi_jetinv    -> GetXaxis() -> SetTitle (Form("#Delta#phi(j,#slash{E_T}) [rad] (EB)"));

	// * Shower shape variables
	histEE_sceta_pho      -> GetXaxis() -> SetTitle (Form("Ch.Iso(#gamma) [GeV] (EE)"));
	histEE_sceta_pho      -> GetXaxis() -> SetTitle (Form("#eta_{SC}(#gamma) (EE)"));
	histEE_scEn_pho       -> GetXaxis() -> SetTitle (Form("#E^{raw}_{SC}(#gamma) [GeV] (EE)"));
	histEE_r9_pho         -> GetXaxis() -> SetTitle (Form("R9(#gamma) [GeV] (EE)"));
	histEE_sigetaeta_pho  -> GetXaxis() -> SetTitle (Form("#sigma_{#eta#eta}(#gamma) (EE)"));
	histEE_sigetaphi_pho  -> GetXaxis() -> SetTitle (Form("#sigma_{#eta#phi}(#gamma) (EE)"));
	histEE_s4_pho         -> GetXaxis() -> SetTitle (Form("E_{2#times2}/E_{5#times5}}(#gamma) (EE)"));
	histEE_etawidth_pho   -> GetXaxis() -> SetTitle (Form("#delta^{SC}_{#eta}(#gamma) (EE)"));
	histEE_phiwidth_pho   -> GetXaxis() -> SetTitle (Form("#delta^{SC}_{#phi}(#gamma) (EE)"));
	histEE_esSigRR_pho    -> GetXaxis() -> SetTitle (Form("E_{ES}(#gamma) [GeV] (EE)"));
	histEE_ESoverSC_pho   -> GetXaxis() -> SetTitle (Form("E_{ES}/E^{raw}_{SC} (EE)"));

	histEB_sceta_pho      -> GetXaxis() -> SetTitle (Form("Ch.Iso(#gamma) [GeV] (EB)"));
	histEB_sceta_pho      -> GetXaxis() -> SetTitle (Form("#eta_{SC}(#gamma) (EB)"));
	histEB_scEn_pho       -> GetXaxis() -> SetTitle (Form("#E^{raw}_{SC}(#gamma) [GeV] (EB)"));
	histEB_r9_pho         -> GetXaxis() -> SetTitle (Form("R9(#gamma) [GeV] (EB)"));
	histEB_sigetaeta_pho  -> GetXaxis() -> SetTitle (Form("#sigma_{#eta#eta}(#gamma) (EB)"));
	histEB_sigetaphi_pho  -> GetXaxis() -> SetTitle (Form("#sigma_{#eta#phi}(#gamma) (EB)"));
	histEB_s4_pho         -> GetXaxis() -> SetTitle (Form("E_{2#times2}/E_{5#times5}}(#gamma) (EB)"));
	histEB_etawidth_pho   -> GetXaxis() -> SetTitle (Form("#delta^{SC}_{#eta}(#gamma) (EB)"));
	histEB_phiwidth_pho   -> GetXaxis() -> SetTitle (Form("#delta^{SC}_{#phi}(#gamma) (EB)"));
}


int FillHistogram (TreeReader &tree_input, int leptype, tuple<int,int,int,int> objID, double scale, float puwei, float genwei)
{
	int ilep1 = get<0> (objID);
	int ilep2 = get<1> (objID);
	int ipho  = get<2> (objID);
	int ijet  = get<3> (objID);

	if (ilep1 == ilep2)   printf ("  |   |-- Error: fuck, lep1 = lep2 = %d!!!\n", ilep1);


	// + List of input
	//----------------
	// * Lepton
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

	float dphilep1inv = compute_DeltaPhi (phiLep1, phiInv);
	float dphilep2inv = compute_DeltaPhi (phiLep2, phiInv);
	float dphiphoinv  = compute_DeltaPhi (phiPho,  phiInv);
	float dphijetinv  = compute_DeltaPhi (phiJet,  phiInv);

	float chIso      = phoPFChIso[ipho];
	float scEta      = phoSCEta[ipho];
	float scRawEn    = phoSCRawE[ipho];
	float r9         = phoR9[ipho];
	float sigetaeta  = phoSigmaIEtaIEtaFull[ipho];
	float sigetaphi  = phoSigmaIEtaIPhiFull[ipho];
	float s4         = phoE2x2Full[ipho] * phoE5x5Full[ipho];
	float wEta       = phoSCEtaWidth[ipho];
	float wPhi       = phoSCPhiWidth[ipho];
	float esSigRR    = phoESEffSigmaRR[ipho];
	float enESoverSC = (phoESEnP1[ipho]+phoESEnP2[ipho]) / phoSCRawE[ipho];

	float enLep1 = lepEn[ilep1];
	float enLep2 = lepEn[ilep2];
	v4d_lep1 . SetPtEtaPhiE (ptLep1, etaLep1, phiLep1, enLep1);
	v4d_lep2 . SetPtEtaPhiE (ptLep2, etaLep2, phiLep2, enLep2);
	v4d_pho  . SetPtEtaPhiM (ptPho,  etaPho,  phiPho,  0);
	v4d_diobj = v4d_lep1 + v4d_lep2;
	v4d_triobj = v4d_diobj + v4d_pho;

	massDiobj  = v4d_diobj . M();
	massTriobj = v4d_triobj . M();

	if (abs(etaPho) < 1.4442)
	{
		// * Tranverse momentum
		histEE_pT_lep1       -> Fill (ptLep1,      scale*puwei*genwei);
		histEE_pT_lep2       -> Fill (ptLep2,      scale*puwei*genwei);
		histEE_pT_pho        -> Fill (ptPho,       scale*puwei*genwei);
		histEE_pT_jet        -> Fill (ptJet,       scale*puwei*genwei);
		histEE_pT_inv        -> Fill (ptInv,       scale*puwei*genwei);

		// * Pseudorapidity
		histEE_eta_lep1      -> Fill (etaLep1,     scale*puwei*genwei);
		histEE_eta_lep2      -> Fill (etaLep2,     scale*puwei*genwei);
		histEE_eta_pho       -> Fill (etaPho,      scale*puwei*genwei);
		histEE_eta_jet       -> Fill (etaJet,      scale*puwei*genwei);
		histEE_eta_inv       -> Fill (etaInv,      scale*puwei*genwei);

		// * Azimuthal angle
		histEE_phi_lep1      -> Fill (phiLep1,     scale*puwei*genwei);
		histEE_phi_lep2      -> Fill (phiLep2,     scale*puwei*genwei);
		histEE_phi_pho       -> Fill (phiPho,      scale*puwei*genwei);
		histEE_phi_jet       -> Fill (phiJet,      scale*puwei*genwei);
		histEE_phi_inv       -> Fill (phiInv,      scale*puwei*genwei);

		// * Mass
		histEE_mass_2body    -> Fill (massDiobj,   scale*puwei*genwei);
		histEE_mass_3body    -> Fill (massTriobj,  scale*puwei*genwei);

		// * Pseudorapidity separation
		histEE_dr_lep1pho    -> Fill (drlep1pho,   scale*puwei*genwei);
		histEE_dr_lep2pho    -> Fill (drlep2pho,   scale*puwei*genwei);
		histEE_dr_lep1jet    -> Fill (drlep1jet,   scale*puwei*genwei);
		histEE_dr_lep2jet    -> Fill (drlep2jet,   scale*puwei*genwei);
		histEE_dr_leplep     -> Fill (drleplep,    scale*puwei*genwei);
		histEE_dr_phojet     -> Fill (drphojet,    scale*puwei*genwei);

		// * Angular separation
		histEE_dphi_lep1inv  -> Fill (dphilep1inv, scale*puwei*genwei);
		histEE_dphi_lep2inv  -> Fill (dphilep2inv, scale*puwei*genwei);
		histEE_dphi_phoinv   -> Fill (dphiphoinv,  scale*puwei*genwei);
		histEE_dphi_jetinv   -> Fill (dphijetinv,  scale*puwei*genwei);

		// * Shower shape variables
		histEE_chIso_pho     -> Fill (chIso,       scale*puwei*genwei);
		histEE_sceta_pho     -> Fill (scEta,       scale*puwei*genwei);
		histEE_scEn_pho      -> Fill (scRawEn,     scale*puwei*genwei);
		histEE_r9_pho        -> Fill (r9,          scale*puwei*genwei);
		histEE_sigetaeta_pho -> Fill (sigetaeta,   scale*puwei*genwei);
		histEE_sigetaphi_pho -> Fill (sigetaphi,   scale*puwei*genwei);
		histEE_s4_pho        -> Fill (s4,          scale*puwei*genwei);
		histEE_etawidth_pho  -> Fill (wEta,        scale*puwei*genwei);
		histEE_phiwidth_pho  -> Fill (wPhi,        scale*puwei*genwei);
		histEE_esSigRR_pho   -> Fill (esSigRR,     scale*puwei*genwei);
		histEE_ESoverSC_pho  -> Fill (enESoverSC,  scale*puwei*genwei);

		return 1;
	}

	// * Tranverse momentum
	histEB_pT_lep1       -> Fill (ptLep1,      scale*puwei*genwei);
	histEB_pT_lep2       -> Fill (ptLep2,      scale*puwei*genwei);
	histEB_pT_pho        -> Fill (ptPho,       scale*puwei*genwei);
	histEB_pT_jet        -> Fill (ptJet,       scale*puwei*genwei);
	histEB_pT_inv        -> Fill (ptInv,       scale*puwei*genwei);

	// * Pseudorapidity
	histEB_eta_lep1      -> Fill (etaLep1,     scale*puwei*genwei);
	histEB_eta_lep2      -> Fill (etaLep2,     scale*puwei*genwei);
	histEB_eta_pho       -> Fill (etaPho,      scale*puwei*genwei);
	histEB_eta_jet       -> Fill (etaJet,      scale*puwei*genwei);
	histEB_eta_inv       -> Fill (etaInv,      scale*puwei*genwei);

	// * Azimuthal angle
	histEB_phi_lep1      -> Fill (phiLep1,     scale*puwei*genwei);
	histEB_phi_lep2      -> Fill (phiLep2,     scale*puwei*genwei);
	histEB_phi_pho       -> Fill (phiPho,      scale*puwei*genwei);
	histEB_phi_jet       -> Fill (phiJet,      scale*puwei*genwei);
	histEB_phi_inv       -> Fill (phiInv,      scale*puwei*genwei);

	// * Mass
	histEB_mass_2body    -> Fill (massDiobj,   scale*puwei*genwei);
	histEB_mass_3body    -> Fill (massTriobj,  scale*puwei*genwei);

	// * Pseudorapidity separation
	histEB_dr_lep1pho    -> Fill (drlep1pho,   scale*puwei*genwei);
	histEB_dr_lep2pho    -> Fill (drlep2pho,   scale*puwei*genwei);
	histEB_dr_lep1jet    -> Fill (drlep1jet,   scale*puwei*genwei);
	histEB_dr_lep2jet    -> Fill (drlep2jet,   scale*puwei*genwei);
	histEB_dr_leplep     -> Fill (drleplep,    scale*puwei*genwei);
	histEB_dr_phojet     -> Fill (drphojet,    scale*puwei*genwei);

	// * Angular separation
	histEB_dphi_lep1inv  -> Fill (dphilep1inv, scale*puwei*genwei);
	histEB_dphi_lep2inv  -> Fill (dphilep2inv, scale*puwei*genwei);
	histEB_dphi_phoinv   -> Fill (dphiphoinv,  scale*puwei*genwei);
	histEB_dphi_jetinv   -> Fill (dphijetinv,  scale*puwei*genwei);

	// * Shower shape variables
	histEB_chIso_pho     -> Fill (chIso,       scale*puwei*genwei);
	histEB_sceta_pho     -> Fill (scEta,       scale*puwei*genwei);
	histEB_scEn_pho      -> Fill (scRawEn,     scale*puwei*genwei);
	histEB_r9_pho        -> Fill (r9,          scale*puwei*genwei);
	histEB_sigetaeta_pho -> Fill (sigetaeta,   scale*puwei*genwei);
	histEB_sigetaphi_pho -> Fill (sigetaphi,   scale*puwei*genwei);
	histEB_s4_pho        -> Fill (s4,          scale*puwei*genwei);
	histEB_etawidth_pho  -> Fill (wEta,        scale*puwei*genwei);
	histEB_phiwidth_pho  -> Fill (wPhi,        scale*puwei*genwei);

	return 1;
}


void  WriteHistogram ()
{
	// * Tranverse momentum
	histEE_pT_lep1       -> Write();
	histEE_pT_lep2       -> Write();
	histEE_pT_pho        -> Write();
	histEE_pT_jet        -> Write();
	histEE_pT_inv        -> Write();

	histEB_pT_lep1       -> Write();
	histEB_pT_lep2       -> Write();
	histEB_pT_pho        -> Write();
	histEB_pT_jet        -> Write();
	histEB_pT_inv        -> Write();

	// * Pseudorapidity
	histEE_eta_lep1      -> Write();
	histEE_eta_lep2      -> Write();
	histEE_eta_pho       -> Write();
	histEE_eta_jet       -> Write();
	histEE_eta_inv       -> Write();

	histEB_eta_lep1      -> Write();
	histEB_eta_lep2      -> Write();
	histEB_eta_pho       -> Write();
	histEB_eta_jet       -> Write();
	histEB_eta_inv       -> Write();

	// * Azimuthal angle
	histEE_phi_lep1      -> Write();
	histEE_phi_lep2      -> Write();
	histEE_phi_pho       -> Write();
	histEE_phi_jet       -> Write();
	histEE_phi_inv       -> Write();

	histEB_phi_lep1      -> Write();
	histEB_phi_lep2      -> Write();
	histEB_phi_pho       -> Write();
	histEB_phi_jet       -> Write();
	histEB_phi_inv       -> Write();

	// * Mass
	histEE_mass_2body    -> Write();
	histEE_mass_3body    -> Write();

	histEB_mass_2body    -> Write();
	histEB_mass_3body    -> Write();

	// * Pseudorapidity separation
	histEE_dr_lep1pho    -> Write();
	histEE_dr_lep2pho    -> Write();
	histEE_dr_lep1jet    -> Write();
	histEE_dr_lep2jet    -> Write();
	histEE_dr_leplep     -> Write();
	histEE_dr_phojet     -> Write();

	histEB_dr_lep1pho    -> Write();
	histEB_dr_lep2pho    -> Write();
	histEB_dr_lep1jet    -> Write();
	histEB_dr_lep2jet    -> Write();
	histEB_dr_leplep     -> Write();
	histEB_dr_phojet     -> Write();

	// * Angular separation
	histEE_dphi_lep1inv  -> Write();
	histEE_dphi_lep2inv  -> Write();
	histEE_dphi_phoinv   -> Write();
	histEE_dphi_jetinv   -> Write();

	histEB_dphi_lep1inv  -> Write();
	histEB_dphi_lep2inv  -> Write();
	histEB_dphi_phoinv   -> Write();
	histEB_dphi_jetinv   -> Write();

	// * Shower shape variables
	histEE_chIso_pho     -> Write();
	histEE_sceta_pho     -> Write();
	histEE_scEn_pho      -> Write();
	histEE_r9_pho        -> Write();
	histEE_sigetaeta_pho -> Write();
	histEE_sigetaphi_pho -> Write();
	histEE_s4_pho        -> Write();
	histEE_etawidth_pho  -> Write();
	histEE_phiwidth_pho  -> Write();
	histEE_esSigRR_pho   -> Write();
	histEE_ESoverSC_pho  -> Write();

	histEB_chIso_pho     -> Write();
	histEB_sceta_pho     -> Write();
	histEB_scEn_pho      -> Write();
	histEB_r9_pho        -> Write();
	histEB_sigetaeta_pho -> Write();
	histEB_sigetaphi_pho -> Write();
	histEB_s4_pho        -> Write();
	histEB_etawidth_pho  -> Write();
	histEB_phiwidth_pho  -> Write();
}


void CleanHistogram ()
{
	// * Tranverse momentum
	delete  histEE_pT_lep1;
	delete  histEE_pT_lep2;
	delete  histEE_pT_pho;
	delete  histEE_pT_jet;
	delete  histEE_pT_inv;

	delete  histEB_pT_lep1;
	delete  histEB_pT_lep2;
	delete  histEB_pT_pho;
	delete  histEB_pT_jet;
	delete  histEB_pT_inv;

	// * Pseudorapidity
	delete  histEE_eta_lep1;
	delete  histEE_eta_lep2;
	delete  histEE_eta_pho;
	delete  histEE_eta_jet;
	delete  histEE_eta_inv;

	delete  histEB_eta_lep1;
	delete  histEB_eta_lep2;
	delete  histEB_eta_pho;
	delete  histEB_eta_jet;
	delete  histEB_eta_inv;

	// * Azimuthal angle
	delete  histEE_phi_lep1;
	delete  histEE_phi_lep2;
	delete  histEE_phi_pho;
	delete  histEE_phi_jet;
	delete  histEE_phi_inv;

	delete  histEB_phi_lep1;
	delete  histEB_phi_lep2;
	delete  histEB_phi_pho;
	delete  histEB_phi_jet;
	delete  histEB_phi_inv;

	// * Mass
	delete  histEE_mass_2body;
	delete  histEE_mass_3body;

	delete  histEB_mass_2body;
	delete  histEB_mass_3body;

	// * Pseudorapidity separation
	delete  histEE_dr_lep1pho;
	delete  histEE_dr_lep2pho;
	delete  histEE_dr_lep1jet;
	delete  histEE_dr_lep2jet;
	delete  histEE_dr_leplep;
	delete  histEE_dr_phojet;

	delete  histEB_dr_lep1pho;
	delete  histEB_dr_lep2pho;
	delete  histEB_dr_lep1jet;
	delete  histEB_dr_lep2jet;
	delete  histEB_dr_leplep;
	delete  histEB_dr_phojet;

	// * Angular separation
	delete  histEE_dphi_lep1inv;
	delete  histEE_dphi_lep2inv;
	delete  histEE_dphi_phoinv;
	delete  histEE_dphi_jetinv;

	delete  histEB_dphi_lep1inv;
	delete  histEB_dphi_lep2inv;
	delete  histEB_dphi_phoinv;
	delete  histEB_dphi_jetinv;

	// * Shower shape variables
	delete  histEE_chIso_pho;
	delete  histEE_sceta_pho;
	delete  histEE_scEn_pho;
	delete  histEE_r9_pho;
	delete  histEE_sigetaeta_pho;
	delete  histEE_sigetaphi_pho;
	delete  histEE_s4_pho;
	delete  histEE_etawidth_pho;
	delete  histEE_phiwidth_pho;
	delete  histEE_esSigRR_pho;
	delete  histEE_ESoverSC_pho;

	delete  histEB_chIso_pho;
	delete  histEB_sceta_pho;
	delete  histEB_scEn_pho;
	delete  histEB_r9_pho;
	delete  histEB_sigetaeta_pho;
	delete  histEB_sigetaphi_pho;
	delete  histEB_s4_pho;
	delete  histEB_etawidth_pho;
	delete  histEB_phiwidth_pho;
}

#endif
