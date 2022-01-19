#ifndef CODEANA_PRESELECT_C
#define CODEANA_PRESELECT_C


#include <stdio.h>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "Utility/untuplizer_v09.h"
#include "Utility/fileBrowser.h"
#include "Utility/puweicalc.h"
#include "Utility/RochesterCorrection/RoccoR.cc"

#include "Plugin/TreePreselect_EventGlobal.h"
#include "Plugin/TreePreselect_Electron.h"
#include "Plugin/TreePreselect_Muon.h"
#include "Plugin/TreePreselect_Photon.h"
#include "Plugin/TreePreselect_Jet.h"
#include "Plugin/TreePreselect_MET.h"

using namespace std;



// + Main function
//================
int CodeAna_Preselect (int year, bool isMC, int leptype, string path_input, string path_output)
{
	// + Timing at job start
	//----------------------
	time_t   time_start = time(0);


	// + Get list of input file
	//-------------------------
	printf ("  |-- Input info:\n");
	printf ("  |   |-- Path to file(s):  [%s]\n", path_input.data());


	// + Create output
	//----------------
	string dir_output = path_output;

	int len_dirOutput = dir_output . length();
	int len_erase     = 0;

	for (int i=len_dirOutput-1; i>-1; i--)
	{
		len_erase ++;
		if (dir_output[i] == '/')
		{
			dir_output . erase (i+1, len_erase-1);
			break;
		}
	}

	string  cmd_mkdirOutput = "mkdir -p  ";
	cmd_mkdirOutput += dir_output;
	system (cmd_mkdirOutput.data());
	printf ("  |-- Dir to output:  [%s]\n", dir_output.data());


	// + Open input file & Create output
	//----------------------------------
	// * Read input tree
	TreeReader  tree_input1 (path_input.data(), "tree_Global");
	TreeReader  tree_input2 (path_input.data(), "tree_Events");

	// * Create output file
	TFile *file_output = new TFile (path_output.data(), "recreate");

	// * Create tree containing global information
	TTree *tree_output1 = new TTree ("tree_Global", "Global information");

	tree_input1 . GetEntry (0);
	Long64_t  nEvent              = tree_input1 . GetLong64 ("nEvent");
	Long64_t  nEvent_Skim         = tree_input1 . GetLong64 ("nEvent_Skim");
	Long64_t  nEvent_HLT          = 0;
	Long64_t  nEvent_Electron     = 0;
	Long64_t  nEvent_Muon         = 0;
	Long64_t  nEvent_Photon       = 0;
	double    nEventNeg           = tree_input1 . GetDouble ("nEventNeg");
	double    nEventNeg_Skim      = tree_input1 . GetDouble ("nEventNeg_Skim");
	double    nEventNeg_HLT       = 0;
	double    nEventNeg_Electron  = 0;
	double    nEventNeg_Muon      = 0;
	double    nEventNeg_Photon    = 0;
	double    nEventPU            = tree_input1 . GetDouble ("nEventPU");
	double    nEventPU_Skim       = tree_input1 . GetDouble ("nEventPU_Skim");
	double    nEventPU_HLT        = 0;
	double    nEventPU_Electron   = 0;
	double    nEventPU_Muon       = 0;
	double    nEventPU_Photon     = 0;
	double    nEventNorm          = tree_input1 . GetDouble ("nEventNorm");
	double    nEventNorm_Skim     = tree_input1 . GetDouble ("nEventNorm_Skim");
	double    nEventNorm_HLT      = 0;
	double    nEventNorm_Electron = 0;
	double    nEventNorm_Muon     = 0;
	double    nEventNorm_Photon   = 0;
	double    luminosity          = tree_input1 . GetDouble ("luminosity");
	double    normfactor          = tree_input1 . GetDouble ("normfactor");
	double    crossSection        = tree_input1 . GetDouble ("crossSection");
	bool      useNewPU            = tree_input1 . GetBool   ("useNewPU");
	int       reprocver           = tree_input1 . GetInt    ("reprocver");
	bool      rejPhoton           = tree_input1 . GetBool   ("rejPhoton");

	printf ("  |   |-- Reproc version:   [%d]\n", reprocver);
	printf ("  |   |-- cross-section:    [%f]\n", crossSection);
	printf ("  |   |-- Do use new PU:    [%d]\n", useNewPU);
	printf ("  |   `-- Do reject photon: [%d]\n", rejPhoton);

	tree_output1 -> Branch ("nEvent",              &nEvent);
	tree_output1 -> Branch ("nEvent_Skim",         &nEvent_Skim);
	tree_output1 -> Branch ("nEvent_HLT",          &nEvent_HLT);
	tree_output1 -> Branch ("nEvent_Electron",     &nEvent_Electron);
	tree_output1 -> Branch ("nEvent_Muon",         &nEvent_Muon);
	tree_output1 -> Branch ("nEvent_Photon",       &nEvent_Photon);
	tree_output1 -> Branch ("nEventNeg",           &nEventNeg);
	tree_output1 -> Branch ("nEventNeg_Skim",      &nEventNeg_Skim);
	tree_output1 -> Branch ("nEventNeg_HLT",       &nEventNeg_HLT);
	tree_output1 -> Branch ("nEventNeg_Electron",  &nEventNeg_Electron);
	tree_output1 -> Branch ("nEventNeg_Muon",      &nEventNeg_Muon);
	tree_output1 -> Branch ("nEventNeg_Photon",    &nEventNeg_Photon);
	tree_output1 -> Branch ("nEventPU",            &nEventPU);
	tree_output1 -> Branch ("nEventPU_Skim",       &nEventPU_Skim);
	tree_output1 -> Branch ("nEventPU_HLT",        &nEventPU_HLT);
	tree_output1 -> Branch ("nEventPU_Electron",   &nEventPU_Electron);
	tree_output1 -> Branch ("nEventPU_Muon",       &nEventPU_Muon);
	tree_output1 -> Branch ("nEventPU_Photon",     &nEventPU_Photon);
	tree_output1 -> Branch ("nEventNorm",          &nEventNorm);
	tree_output1 -> Branch ("nEventNorm_Skim",     &nEventNorm_Skim);
	tree_output1 -> Branch ("nEventNorm_HLT",      &nEventNorm_HLT);
	tree_output1 -> Branch ("nEventNorm_Electron", &nEventNorm_Electron);
	tree_output1 -> Branch ("nEventNorm_Muon",     &nEventNorm_Muon);
	tree_output1 -> Branch ("nEventNorm_Photon",   &nEventNorm_Photon);
	tree_output1 -> Branch ("luminosity",          &luminosity);
	tree_output1 -> Branch ("normfactor",          &normfactor);
	tree_output1 -> Branch ("crossSection",        &crossSection);

	// * Create tree containing event information
	TTree *tree_output2 = new TTree ("tree_Events", "Events information");
	BranchPreselect_EventGlobal (tree_output2);
	BranchPreselect_Electron    (tree_output2);
	BranchPreselect_Muon        (tree_output2);
	BranchPreselect_Photon      (tree_output2);
	BranchPreselect_Jet         (tree_output2);
	BranchPreselect_MET         (tree_output2);


	// + Getting info from additional package
	//---------------------------------------
	// * Rochester correction
	TString tpath_input = path_input.data();

	bool isPreVFP = (reprocver==2);
	isPreVFP |= tpath_input.Contains("RunB");
	isPreVFP |= tpath_input.Contains("RunC");
	isPreVFP |= tpath_input.Contains("RunD");
	isPreVFP |= tpath_input.Contains("RunE");
	isPreVFP |= tpath_input.Contains("RunF1");

	bool isPostVFP = (reprocver==2);
	isPostVFP |= tpath_input.Contains("RunF2");
	isPostVFP |= tpath_input.Contains("RunG");
	isPostVFP |= tpath_input.Contains("RunH");

	TString path_roccor = Form ("Utility/RochesterCorrection/RoccoR%dUL.txt", year);
	if (reprocver != 2)   path_roccor = Form ("Utility/RochesterCorrection/RoccoR%d.txt", year);
	if (isPreVFP)   path_roccor = "Utility/RochesterCorrection/RoccoR2016aUL.txt";
	if (isPostVFP)   path_roccor = "Utility/RochesterCorrection/RoccoR2016bUL.txt";

	if (isMC)   path_roccor = Form ("Utility/RochesterCorrection/RoccoR%d.txt", year);

	RoccoR  rcCore;
	rcCore . init (path_roccor.Data());

	// * PU calculator
	PUWeightCalculator puCal;

	string pathPU = "PileupWeight/summer16/PU_histo_13TeV_2016_GoldenJSON_69200nb.root";

	if (year==2017)
	{
		pathPU = "PileupWeight/fall17/PU_histo_13TeV_2017_GoldenJSON_69200nb.root";
		if (useNewPU)   pathPU = "PileupWeight/fall17_corrected/PU_correctedPU_13TeV_2017_GoldenJSON_69200nb.root";
	}
	else if (year==2018)
	{
		pathPU = "PileupWeight/autumn18/PU_histo_13TeV_2018_GoldenJSON_69200nb.root";
	}

	puCal . Init (pathPU.data());


	// + Timing at loop start
	//-----------------------
	time_t time_read = time(0);


	// + Read the input tree
	//----------------------
	long nEntry = tree_input2 . GetEntriesFast();
	printf ("  |-- Found:          [%ld] events\n", nEntry);

	bool passHLT;
	bool passElectron;
	bool passMuon;
	bool passPhoton;

	int stt_HLT;
	int stt_Electron;
	int stt_Muon;
	int stt_Photon;
	int stt_Jet;
	int stt_MET;

	for (long ev=0; ev<nEntry; ev++)
	{
		tree_input2 . GetEntry (ev);


		// * Read the event global variable
		stt_HLT = FillPreselect_EventGlobal (tree_input2, puCal, year, isMC, leptype);
		passHLT = (stt_HLT == 1);
		if (!passHLT)   continue;

		nEvent_HLT     += 1;
		nEventNeg_HLT  += genWeight;
		nEventPU_HLT   += genWeight * puWeight;
		nEventNorm_HLT += genWeight * puWeight;

		// * Read the electron
		stt_Electron = FillPreselect_Electron (tree_input2);
		passElectron = (stt_Electron == 1);
		if (leptype==1 && !passElectron)   continue;

		nEvent_Electron     += 1;
		nEventNeg_Electron  += genWeight;
		nEventPU_Electron   += genWeight * puWeight;
		nEventNorm_Electron += genWeight * puWeight;

		// * Read the muon
		stt_Muon = FillPreselect_Muon (tree_input2, rcCore, isMC);
		passMuon = (stt_Muon == 1);
		if (leptype==2 && !passMuon)   continue;

		nEvent_Muon     += 1;
		nEventNeg_Muon  += genWeight;
		nEventPU_Muon   += genWeight * puWeight;
		nEventNorm_Muon += genWeight * puWeight;

		// * Read the photon
		stt_Photon = FillPreselect_Photon (tree_input2, isMC, rejPhoton);
		passPhoton = (stt_Photon == 1);
		if (!passPhoton)   continue;
		/*if (!passPhoton)
		{
			if (stt_Photon == 2)
			{
				printf ("  |   |   `-- Reject double-counting event\n");
				continue;
			}
			printf ("  |   |   `-- Failed\n");
			continue;
		}*/

		nEvent_Photon     += 1;
		nEventNeg_Photon  += genWeight;
		nEventPU_Photon   += genWeight * puWeight;
		nEventNorm_Photon += genWeight * puWeight;

		// * Read the jet
		stt_Jet = FillPreselect_Jet (tree_input2, year, reprocver);

		// * Read the missing ET
		stt_MET = FillPreselect_MET (tree_input2, isMC, year, run, nVtx, reprocver);


		// * Write to tree
		tree_output2 -> Fill();
		//printf ("  |   |   `-- Pass\n");
	}

	printf ("  |-- Selected:       [%lld] events\n", nEvent_Photon);


	// + Fill the global tree
	//-----------------------
	// * Get the normalized number of events
	nEventNorm_HLT      *= normfactor * crossSection;
	nEventNorm_Electron *= normfactor * crossSection;
	nEventNorm_Muon     *= normfactor * crossSection;
	nEventNorm_Photon   *= normfactor * crossSection;

	// * ACtually fill the tree
	tree_output1 -> Fill();


	// + Write to file, free memory
	//-----------------------------
	// * Write tree to file
	tree_output1 -> Write ("", TObject::kOverwrite);
	tree_output2 -> Write ("", TObject::kOverwrite);

	// Free memory
	delete tree_output1;
	delete tree_output2;
	delete file_output;

	printf ("  |-- Save output at: [%s]\n", path_output.data());


	// + Timing at the end
	//--------------------
	time_t time_end  = time(0);

	float dt_prep  = (time_read - time_start) / 3600.0;
	float dt_work  = (time_end - time_read) / 3600.0;
	float dt_total = (time_end - time_start) / 3600.0;

	printf ("  `-- Job's done:\n");
	printf ("      |-- Prep time:   [%.3f] hours\n", dt_prep);
	printf ("      |-- Work time:   [%.3f] hours\n", dt_work);
	printf ("      `-- Total time:  [%.3f] hours\n", dt_total);

	return 0;
}


#endif
