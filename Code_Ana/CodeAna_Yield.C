#include <stdio.h>
#include <iostream>

#include "TFile.h"
#include "TTree.h"

#include "Utility/fileBrowser.h"

using namespace std;



vector<string> list_variable;
vector<string> list_step;
int  nVariable;

string nametype[4] =
{
	"",
	"Neg",
	"PU",
	"Norm"
};



void  Init_listVariable (int ytype)
{
	// + List of variable
	//-------------------
	vector<string> list_tmp;
	list_tmp . clear();

	list_tmp . push_back ("nEvent*");
	list_tmp . push_back ("nEvent*_Skim");
	list_tmp . push_back ("nEvent*_HLT");
	list_tmp . push_back ("nEvent*_Electron");
	list_tmp . push_back ("nEvent*_Muon");
	list_tmp . push_back ("nEvent*_Photon");
	list_tmp . push_back ("nEvent*_Final");

	list_step . clear();
	list_step . push_back ("#event");
	list_step . push_back ("pass HLT");
	list_step . push_back ("pass electron");
	list_step . push_back ("pass muon");
	list_step . push_back ("pass phton");
	list_step . push_back ("final yield");

	int nvar = list_tmp . size();


	list_variable . clear();

	for (int i=0; i<nvar; i++)
	{
		string namevar = Replace_StrByStr (list_tmp[i], nametype[ytype], 0);
		list_variable . push_back (namevar);
	}

	nVariable = list_variable . size();
}



vector<double>  Get_Yields (string pathtofile, int ytype)
{
	TFile *filein = new TFile (pathtofile.data(), "read");

	TTree *treein = (TTree*)filein -> Get ("tree_Global");

	vector<double>  list_tmp;
	list_tmp . clear();

	for (int i=0; i<nVariable; i++)
	{
		double    yieldFloat = 0.0;

		list_tmp   . push_back (yieldFloat);
	}


	for (int i=0; i<nVariable; i++)
	{
		treein -> SetBranchAddress (list_variable[i].data(), &list_tmp[i]);
	}

	treein -> GetEntry (0);

	vector<double> result;
	result . clear();

	for (int i=0; i<nVariable; i++)
	{
		result . push_back (list_tmp[i]);
	}

	delete treein;

	filein -> Close();
	delete filein;

	return result;
}




int CodeAna_Yield (int year,  int leptype,  int region,  int ytype,  bool printall)
{
	// + Predefined directory
	//-----------------------
	string loc_input = "/home/hoa/Task_ZgSMP/Output/Hist*";

	string subdir_region[2] =
	{
		"Region_Signal",
		"Region_Sideband"
	};

	string yearchk = "hist";
	yearchk += to_string (year-2000);

	string lepchk  = (leptype==1) ? "Electron" : "Muon";

	string dir_input = loc_input;
	dir_input += "/";
	dir_input += subdir_region[region];
	dir_input += "/";
	dir_input += yearchk;
	dir_input += "*";
	dir_input += lepchk;
	dir_input += "*";

	printf ("%s\n", dir_input.data());


	// + List of input path
	//---------------------
	// * All files
	pair<vector<string>,bool> fbrowser = fileBrowser (dir_input);
	vector<string>  list_pathinput = fbrowser . first;
	bool            stt_browser    = fbrowser . second;
	int             len_listInput  = list_pathinput . size();

	// * Data files
	vector<string>  list_pathinputDT;
	list_pathinputDT . clear();

	for (int i=0; i<len_listInput; i++)
	{
		string pathtofile = list_pathinput[i];
		bool match = Check_StrInStr ("HistMC", pathtofile);

		if (match)   list_pathinputDT . push_back (pathtofile);
	}

	int nDTpath = list_pathinputDT . size();

	// * MC files
	vector<string>  list_pathinputMC;
	list_pathinputMC . clear();

	for (int i=0; i<len_listInput; i++)
	{
		string pathtofile = list_pathinput[i];
		bool match = Check_StrInStr ("HistMC", pathtofile);

		if (match)   list_pathinputMC . push_back (pathtofile);
	}

	int nMCpath = list_pathinputMC . size();


	// + Read data from file
	//----------------------
	// * Initialize the list of variables
	Init_listVariable (ytype);

	// * Get the data yield
	vector<vector<double>>  list_yieldDT;
	list_yieldDT . clear();

	vector<double> list_yieldbystep;

	for (int i=0; i<nDTpath; i++)
	{
		string pathtofile = list_pathinputDT[i];

		list_yieldbystep . clear();
		list_yieldbystep = Get_Yields (pathtofile, ytype);

		list_yieldDT . push_back (list_yieldbystep);
	}

	list_yieldbystep . clear();
	for (int i=0; i<nVariable; i++)
	{
		double yieldSum = 0.0;

		for (int j=0; j<nDTpath; j++)
		{
			yieldSum += list_yieldDT[j][i];
		}

		list_yieldbystep . push_back (yieldSum);
	}
	list_yieldDT . push_back (list_yieldbystep);

	// * Get the MC yield
	vector<vector<double>>  list_yieldMC;
	list_yieldMC . clear();

	for (int i=0; i<nMCpath; i++)
	{
		string pathtofile = list_pathinputMC[i];

		list_yieldbystep . clear();
		list_yieldbystep = Get_Yields (pathtofile, ytype);

		list_yieldMC . push_back (list_yieldbystep);
	}

	list_yieldbystep . clear();
	for (int i=0; i<nVariable; i++)
	{
		double yieldSum = 0.0;

		for (int j=0; j<nMCpath; j++)
		{
			yieldSum += list_yieldMC[j][i];
		}

		list_yieldbystep . push_back (yieldSum);
	}
	list_yieldMC . push_back (list_yieldbystep);


	// + Print to file
	//----------------
	// * Path to output
	string path_output = "/home/hoa/Task_ZgSMP/Output/Yield_DataMC/";
	path_output += subdir_region[region];
	path_output += "/yield";
	path_output += to_string (year-2000);
	path_output += "_";
	path_output += lepchk;
	path_output += "_";
	path_output += nametype[ytype];
	path_output += ".csv";

	FILE *fileout = fopen (path_output.data(), "w");

	// * Print the title
	fprintf (fileout, "filename");

	for (int j=0; j<nVariable; j++)
	{
		fprintf (fileout, ",%s", list_step[j].data());
	}

	fprintf (fileout, "\n");

	// * Print the data
	for (int i=0; i<nDTpath; i++)
	{
		fprintf (fileout, "%s", list_pathinputDT[i].data());

		for (int j=0; j<nVariable; j++)
		{
			fprintf (fileout, ",%.2f", list_yieldDT[i][j]);
		}
	}

	for (int j=0; j<nVariable; j++)
	{
		fprintf (fileout, ",%.2f", list_yieldDT[nDTpath][j]);
	}

	// * Print the data
	for (int i=0; i<nMCpath; i++)
	{
		fprintf (fileout, "%s", list_pathinputMC[i].data());

		for (int j=0; j<nVariable; j++)
		{
			fprintf (fileout, ",%.2f", list_yieldMC[i][j]);
		}
	}

	for (int j=0; j<nVariable; j++)
	{
		fprintf (fileout, ",%.2f", list_yieldMC[nMCpath][j]);
	}

	fclose (fileout);

	return 0;
}
