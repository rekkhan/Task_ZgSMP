#ifndef CODEANA_SKIM_C
#define CODEANA_SKIM_C

#include <stdio.h>
#include <iostream>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"

#include "Utility/untuplizer_v09.h"
#include "Utility/fileBrowser.h"

#include "Plugin/TreeSkim_EventGlobal.h"
#include "Plugin/TreeSkim_Electron.h"
#include "Plugin/TreeSkim_Muon.h"
#include "Plugin/TreeSkim_Photon.h"
#include "Plugin/TreeSkim_Jet.h"
#include "Plugin/TreeSkim_MET.h"
#include "Plugin/TreeSkim_MC.h"

#include "Plugin/Select_Event.h"
#include "Plugin/Select_Lepton.h"
#include "Plugin/Select_Photon.h"

using namespace std;



// + Main function
//----------------
int  CodeAna_Skim (bool isMC,  double xsection,  bool rejpho,  int reproc,  int year,  string path_input,  string path_output)
{
	// + Timing at job start
	//----------------------
	time_t   time_start = time(0);


	// + Get list of input file
	//-------------------------
	printf ("  |-- Input info:\n");
	printf ("  |   |-- Path to file(s):  [%s]\n", path_input.data());
	printf ("  |   |-- Reproc version:   [%d]\n", reproc);
	printf ("  |   |-- cross-section:    [%f]\n", xsection);
	printf ("  |   `-- Reject photon:    [%d]\n", rejpho);

	pair<vector<string>,bool>  info_pathInput = fileBrowser (path_input, "root");
	vector<string>  list_pathInput = info_pathInput . first;
	bool workfine = info_pathInput . second;

	int len_listPathInput = list_pathInput . size();

	if (len_listPathInput<1 || !workfine)
	{
		printf ("  `-- Error: No input found\n");
		return 1;
	}

	// * Remove broken file (temporary fix)
	vector<string>::iterator its;
	for (its=list_pathInput.begin(); its<list_pathInput.end(); its++)
	{
		if (*its == "/data1/ggNtuples/V10_02_10_07/job_DoubleEG_Run2016B_Legacy/ggtree_data_3-41.root")
		{
			list_pathInput . erase (its);
			its --;
		}

		if (*its == "/data1/ggNtuples/V10_02_10_07/job_DoubleEG_Run2017C_MarReminiAOD/ggtree_data_1-1.root")
		{
			list_pathInput . erase (its);
			its --;
		}
	}


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
	TreeReader  tree_input (list_pathInput, "ggNtuplizer/EventTree");

	// * Create output file
	TFile *file_output = new TFile (path_output.data(), "recreate");

	// * Create tree containing global information
	TTree *tree_output1 = new TTree ("tree_Global", "Global information");

	Long64_t  nEvent          = 0;
	Long64_t  nEvent_Skim     = 0;
	double    nEventNeg       = 0;
	double    nEventNeg_Skim  = 0;
	double    nEventPU        = 0.0;
	double    nEventPU_Skim   = 0.0;
	double    nEventNorm      = 0.0;
	double    nEventNorm_Skim = 0.0;
	double    luminosity      = 0.0;
	double    normfactor      = 0.0;
	double    crossSection    = 0.0;
	bool      useNewPU        = 0;
	int       reprocver       = 0;

	tree_output1 -> Branch ("nEvent",           &nEvent);
	tree_output1 -> Branch ("nEvent_Skim",      &nEvent_Skim);
	tree_output1 -> Branch ("nEventNeg",        &nEventNeg);
	tree_output1 -> Branch ("nEventNeg_Skim",   &nEventNeg_Skim);
	tree_output1 -> Branch ("nEventPU",         &nEventPU);
	tree_output1 -> Branch ("nEventPU_Skim",    &nEventPU_Skim);
	tree_output1 -> Branch ("nEventNorm",       &nEventNorm);
	tree_output1 -> Branch ("nEventNorm_Skim",  &nEventNorm_Skim);
	tree_output1 -> Branch ("luminosity",       &luminosity);
	tree_output1 -> Branch ("normfactor",       &normfactor);
	tree_output1 -> Branch ("crossSection",     &crossSection);
	tree_output1 -> Branch ("useNewPU",         &useNewPU);
	tree_output1 -> Branch ("reprocver",        &reprocver);
	tree_output1 -> Branch ("rejPhoton",        &rejpho);

	// * Create tree for events
	TTree *tree_output2 = new TTree ("tree_Events", "Events information");
	BranchSkim_EventGlobal (tree_output2);
	BranchSkim_Electron    (tree_output2);
	BranchSkim_Muon        (tree_output2);
	BranchSkim_Photon      (tree_output2);
	BranchSkim_Jet         (tree_output2);
	BranchSkim_MET         (tree_output2);
	if (isMC)   BranchSkim_MC (tree_output2);


	// + Timing at loop start
	//-----------------------
	time_t time_read = time(0);


	// + Read and write - Event info
	//------------------------------
	nEvent = tree_input . GetEntriesFast();
	printf ("  |-- Found:          [%lld] events\n", nEvent);

	bool passEvent;
	bool passLepton;
	bool passPhoton;
	float genWeiTmp;

	//for (long ev=0; ev<2000; ev++)
	for (long ev=0; ev<nEvent; ev++)
	{
		// + Intial step
		//--------------
		// * Read the entry
		tree_input . GetEntry (ev);

		// * Get the generator weight
		genWeiTmp = 1.0;

		if (isMC)
		{
			genWeiTmp = tree_input . GetFloat ("genWeight");

			genWeiTmp = (genWeiTmp>0) ? 1 : -1;
		}

		nEventNeg  += genWeiTmp;
		nEventPU   += genWeiTmp;
		nEventNorm += genWeiTmp;


		// + Apply selection
		//------------------
		passEvent = SelectEvent_Skim (tree_input, year);
		if (!passEvent)   continue;

		passLepton = SelectLepton_Skim (tree_input);
		if (!passLepton)   continue;

		passPhoton = SelectPhoton_Skim (tree_input);
		if (!passPhoton)   continue;

		nEvent_Skim     += 1;
		nEventNeg_Skim  += genWeiTmp;
		nEventPU_Skim   += genWeiTmp;
		nEventNorm_Skim += genWeiTmp;


		// + Obtain the value from file
		//-----------------------------
		// * Event info
		FillSkim_EventGlobal (tree_input, year, isMC);

		// * Lepton info
		FillSkim_Electron (tree_input);
		FillSkim_Muon     (tree_input);

		// * Photon info
		FillSkim_Photon (tree_input);

		// * Jet & MET info
		FillSkim_Jet (tree_input, isMC);
		FillSkim_MET (tree_input, isMC);

		// * MC info
		if (isMC)   FillSkim_MC (tree_input);


		// + Fill tree
		//------------
		tree_output2 -> Fill();
	}

	printf ("  |-- Selected:       [%lld] events\n", nEvent_Skim);


	// + Get global info
	//------------------
	// * Get luminosity
	luminosity = 35911;
	if (year == 2017)   luminosity = 41526;
	else if (year == 2018)   luminosity = 59402;

	// * Get cross-section
	crossSection = xsection;

	// * Get normalizing factor
	normfactor = luminosity / nEventNeg;

	// * Get normalized #event
	nEventNorm      *= normfactor * xsection;
	nEventNorm_Skim *= normfactor * xsection;

	// * Get PU choice info
	TString tmpInput = path_input . data();
	useNewPU = tmpInput . Contains ("_newPU_");

	// * Get reprocessing version
	reprocver = reproc;

	// * Fill tree
	tree_output1 -> Fill();


	// + Write to file
	//----------------
	tree_output1 -> Write ("", TObject::kOverwrite);
	tree_output2 -> Write ("", TObject::kOverwrite);

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
