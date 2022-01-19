#ifndef CODEANA_SELECT_C
#define CODEANA_SELECT_C


#include <stdio.h>
#include <iostream>

#include "Utility/untuplizer_v09.h"

#include "Plugin/Select_Event.h"
#include "Plugin/Histogram_EventSelection.h"

using namespace std;


// + Main function
//----------------
int CodeAna_Select (int year, bool isMC, int reproc, int leptype, string path_input, int region, int isoPre, int isoSel)
{
	// + Timing at job start
	//----------------------
	time_t   time_start = time(0);


	// + Get list of input file
	//-------------------------
	printf ("  |-- Basic info:\n");
	printf ("  |   |-- Path to file(s):  [%s]\n", path_input.data());


	// + Create output
	//----------------
	// * subdirectories
	string subdir_region[2] =
	{
		"Region_Signal",
		"Region_Sideband"
	};

	// * Initialize the directory
	string dir_output = path_input;

	int len_dirOutput = dir_output . length();
	int len_erase     = 0;

	// * Rename the 'Tree_Preselect...' to 'Hist_...'
	int countslash = 0;
	for (int i=len_dirOutput-1; i>-1; i--)
	{
		len_erase ++;
		if (dir_output[i] == '/')
		{
			dir_output . erase (i+1, len_erase-1);
			countslash ++;
		}

		if (countslash > 1)   break;
	}

	dir_output += (isMC) ? "HistMC" : "HistDT";
	dir_output += (reproc==2) ? "UL/" : "LR/";
	dir_output += subdir_region[region];
	dir_output += "/";

	// * Subdir for photon ch.Iso type
	string subdir_isoPre = (isoPre==0) ? "Worst" : "Correct";
	string subdir_isoSel = (isoSel==0) ? "Worst" : "Correct";
	printf ("  |   |-- ch.Iso @ Pre.Sel. step: [%s]\n", subdir_isoPre.data());
	printf ("  |   |-- ch.Iso @ Sel. step:     [%s]\n", subdir_isoSel.data());

	dir_output += "IsoType_";
	dir_output += subdir_isoPre;
	dir_output += subdir_isoSel;
	dir_output += "/";

	// * Create the directory
	string  cmd_mkdirOutput = "mkdir -p  ";
	cmd_mkdirOutput += dir_output;
	system (cmd_mkdirOutput.data());
	printf ("  |   |-- Dir to output:  [%s]\n", dir_output.data());

	// * Path to the output file
	string path_output = dir_output;
	string filename = "";

	for (int i=len_dirOutput; i>-1; i--)
	{
		if (path_input[i]=='/')   break;
		filename . insert (filename.begin(), path_input[i]);
	}

	filename . replace (0,4,"hist");
	path_output += filename;


	// + Open input file & Create output
	//----------------------------------
	// * Read input tree
	TreeReader  tree_input1 (path_input.data(), "tree_Global");
	TreeReader  tree_input2 (path_input.data(), "tree_Events");

	// * Create output file
	TFile *file_output = new TFile (path_output.data(), "recreate");

	// * Create tree containing global information
	TTree *tree_output = new TTree ("tree_Global", "Global information");

	tree_input1 . GetEntry (0);
	Long64_t  nEvent              = tree_input1 . GetLong64 ("nEvent");
	Long64_t  nEvent_Skim         = tree_input1 . GetLong64 ("nEvent_Skim");
	Long64_t  nEvent_HLT          = tree_input1 . GetLong64 ("nEvent_HLT");
	Long64_t  nEvent_Electron     = tree_input1 . GetLong64 ("nEvent_Electron");
	Long64_t  nEvent_Muon         = tree_input1 . GetLong64 ("nEvent_Muon");
	Long64_t  nEvent_Photon       = tree_input1 . GetLong64 ("nEvent_Photon");
	Long64_t  nEvent_Final        = 0;
	double    nEventNeg           = tree_input1 . GetDouble ("nEventNeg");
	double    nEventNeg_Skim      = tree_input1 . GetDouble ("nEventNeg_Skim");
	double    nEventNeg_HLT       = tree_input1 . GetDouble ("nEventNeg_HLT");
	double    nEventNeg_Electron  = tree_input1 . GetDouble ("nEventNeg_Electron");
	double    nEventNeg_Muon      = tree_input1 . GetDouble ("nEventNeg_Muon");
	double    nEventNeg_Photon    = tree_input1 . GetDouble ("nEventNeg_Photon");
	double    nEventNeg_Final     = 0.0;
	double    nEventPU            = tree_input1 . GetDouble ("nEventPU");
	double    nEventPU_Skim       = tree_input1 . GetDouble ("nEventPU_Skim");
	double    nEventPU_HLT        = tree_input1 . GetDouble ("nEventPU_HLT");
	double    nEventPU_Electron   = tree_input1 . GetDouble ("nEventPU_Electron");
	double    nEventPU_Muon       = tree_input1 . GetDouble ("nEventPU_Muon");
	double    nEventPU_Photon     = tree_input1 . GetDouble ("nEventPU_Photon");
	double    nEventPU_Final      = 0.0;
	double    nEventNorm          = tree_input1 . GetDouble ("nEventNorm");
	double    nEventNorm_Skim     = tree_input1 . GetDouble ("nEventNorm_Skim");
	double    nEventNorm_HLT      = tree_input1 . GetDouble ("nEventNorm_HLT");
	double    nEventNorm_Electron = tree_input1 . GetDouble ("nEventNorm_Electron");
	double    nEventNorm_Muon     = tree_input1 . GetDouble ("nEventNorm_Muon");
	double    nEventNorm_Photon   = tree_input1 . GetDouble ("nEventNorm_Photon");
	double    nEventNorm_Final    = 0.0;
	double    luminosity          = tree_input1 . GetDouble ("luminosity");
	double    normfactor          = (isMC) ? tree_input1 . GetDouble ("normfactor") : 1.0;
	double    crossSection        = (isMC) ? tree_input1 . GetDouble ("crossSection") : 1.0;

	printf ("  |   `-- cross-section:    [%f]\n", crossSection);

	tree_output -> Branch ("nEvent",              &nEvent);
	tree_output -> Branch ("nEvent_Skim",         &nEvent_Skim);
	tree_output -> Branch ("nEvent_HLT",          &nEvent_HLT);
	tree_output -> Branch ("nEvent_Electron",     &nEvent_Electron);
	tree_output -> Branch ("nEvent_Muon",         &nEvent_Muon);
	tree_output -> Branch ("nEvent_Photon",       &nEvent_Photon);
	tree_output -> Branch ("nEvent_Final",        &nEvent_Final);
	tree_output -> Branch ("nEventNeg",           &nEventNeg);
	tree_output -> Branch ("nEventNeg_Skim",      &nEventNeg_Skim);
	tree_output -> Branch ("nEventNeg_HLT",       &nEventNeg_HLT);
	tree_output -> Branch ("nEventNeg_Electron",  &nEventNeg_Electron);
	tree_output -> Branch ("nEventNeg_Muon",      &nEventNeg_Muon);
	tree_output -> Branch ("nEventNeg_Photon",    &nEventNeg_Photon);
	tree_output -> Branch ("nEventNeg_Final",     &nEventNeg_Final);
	tree_output -> Branch ("nEventPU",            &nEventPU);
	tree_output -> Branch ("nEventPU_Skim",       &nEventPU_Skim);
	tree_output -> Branch ("nEventPU_HLT",        &nEventPU_HLT);
	tree_output -> Branch ("nEventPU_Electron",   &nEventPU_Electron);
	tree_output -> Branch ("nEventPU_Muon",       &nEventPU_Muon);
	tree_output -> Branch ("nEventPU_Photon",     &nEventPU_Photon);
	tree_output -> Branch ("nEventPU_Final",      &nEventPU_Final);
	tree_output -> Branch ("nEventNorm",          &nEventNorm);
	tree_output -> Branch ("nEventNorm_Skim",     &nEventNorm_Skim);
	tree_output -> Branch ("nEventNorm_HLT",      &nEventNorm_HLT);
	tree_output -> Branch ("nEventNorm_Electron", &nEventNorm_Electron);
	tree_output -> Branch ("nEventNorm_Muon",     &nEventNorm_Muon);
	tree_output -> Branch ("nEventNorm_Photon",   &nEventNorm_Photon);
	tree_output -> Branch ("nEventNorm_Final",    &nEventNorm_Final);
	tree_output -> Branch ("luminosity",          &luminosity);
	tree_output -> Branch ("normfactor",          &normfactor);
	tree_output -> Branch ("crossSection",        &crossSection);

	// * Initialize the histogram
	InitHistogram (leptype, region);


	// + Timing at loop start
	//-----------------------
	time_t time_read = time(0);


	// + Read the input file
	//----------------------
	long nEntry = tree_input2 . GetEntriesFast();
	printf ("  |-- Found:          [%ld] events\n", nEntry);

	pair<int,tuple<int,int,int,int>>  selector;
	tuple<int,int,int,int> objectID;
	int stt_selection;

	double scale = normfactor * crossSection;
	float  genWeight;
	float  puWeight;
	int    dummy;

	for (long ev=0; ev<nEntry; ev++)
	{
		tree_input2 . GetEntry (ev);

		// * Select the events
		selector = SelectEvent_Final_Squeeze (tree_input2, region, leptype, isoPre, isoSel);
		stt_selection = selector . first;
		objectID      = selector . second;

		if (stt_selection==0)   continue;

		nEvent_Final     += 1;
		nEventNeg_Final  += genWeight;
		nEventPU_Final   += genWeight*puWeight;
		nEventNorm_Final += genWeight*puWeight;

		// * Fill the histograms
		genWeight = tree_input2 . GetFloat ("genWeight");
		puWeight  = tree_input2 . GetFloat ("puWeight");

		dummy = FillHistogram (tree_input2, leptype, objectID, scale, puWeight, genWeight);
	}

	printf ("  |-- Selected:       [%lld] events\n", nEvent_Final);


	// + Write data to file
	//---------------------
	// * Get the weighted #events
	nEventNorm_Final *= scale;

	// * navigate to the file
	file_output -> cd();

	// * Write tree to file
	tree_output -> Fill();
	tree_output -> Write ("", TObject::kOverwrite);

	// * Write histograms to file
	WriteHistogram();

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

	return 1;
}


#endif
