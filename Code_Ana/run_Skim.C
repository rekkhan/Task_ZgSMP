#include <stdio.h>
#include <iostream>

#include "Utility/untuplizer_v09.h"

#include "Plugin/ListPath.h"

#include "CodeAna_Skim.C"


int  run_Skim (bool isMC=0,  int reproc=1,  int year=2016,  int leptype=1,  int file1=1,  int file2=1)
{
	// + Create the list
	//------------------
	vector<vector<int>>  list_nInput;
	list_nInput . clear();
	vector<vector<vector<fInfo>>>  list_infoInput = Fill_ListPath (1, isMC, list_nInput, reproc, 1);

	vector<vector<int>>  list_nOutput;
	list_nOutput . clear();
	vector<vector<vector<fInfo>>>  list_dirOutput = Fill_ListPath (2, isMC, list_nOutput, reproc, 1);



	// + Welcome messages
	//-------------------
	// * Check the parameters
	bool  valid_year     = year>2015 && year<2019;
	bool  valid_leptype  = leptype>0 && leptype<3;
	bool  valid_reproc   = reproc>0 && reproc<3;
	bool  valid_filetype = isMC==0 || isMC==1;
	bool  valid_para = valid_year && valid_leptype && valid_reproc && valid_filetype;

	if (!valid_para)
	{
		printf (" Error:\n");
		if (!valid_year)
		{
			printf (" [!] Year [%d] is not valid, must be in the range [2016,2018]\n", year);
		}
		if (!valid_leptype)
		{
			printf (" [!] lepton type [%d] is invalid, must be:\n", leptype);
			printf ("  |-- 1: electron\n");
			printf ("  `-- 2: muon\n");
		}
		if (!valid_reproc)
		{
			printf (" [!] Reproc version's boolean value [%d] is invalid, must be:\n", reproc);
			printf ("  |-- 1: Legacy\n");
			printf ("  `-- 2: Ultra-legacy\n");
		}
		if (!valid_filetype)
		{
			printf (" [!] File type's boolean value [%d] is invalid, must be 0(false) or 1(true)\n", isMC);
		}
		printf (" [!] Escape now\n");
		return 0;
	}

	// * Check if input and output match
	int nUnmatch = 0;
	int nOutput = 0;
	int nInput  = 0;

	for (int i=0; i<2; i++)
	{
		for (int j=0; j<3; j++)
		{
			nInput  += list_nInput[i][j];
			nOutput += list_nOutput[i][j];

			if (list_nInput[i][j] != list_nOutput[i][j])
			{
				nUnmatch++;

				/*
				printf (" ** Input:\n");
				for (int k=0; k<list_infoInput[i][j].size(); k++)
				{
					printf (" ***** %s\n", list_infoInput[i][j][k].path.data());
				}

				printf (" ** Output:\n");
				for (int k=0; k<list_dirOutput[i][j].size(); k++)
				{
					printf (" ***** %s\n", list_dirOutput[i][j][k].path.data());
				}

				printf ("\n");
				*/
			}
		}
	}

	bool match_InOut = nUnmatch == 0;

	if (!match_InOut)
	{
		printf (" Error:\n");
		printf ("Numer of inputs [%d] doesn't match number of outputs [%d]\n", nInput, nOutput);
		printf (" [!] Escape now\n");
		return 0;
	}

	// * Print welcome message if all are ok
	string str_dttype[2]  = {"Data", "MC"};
	string str_reproc[2]  = {"Legacy", "Ultra-legacy"};
	string str_leptype[2] = {"electron", "muon"};

	int len_dttype  = str_dttype[isMC]  . length();
	int len_reproc  = str_reproc[reproc-1]  . length();
	int len_leptype = str_leptype[leptype-1] . length();

	printf ("\n");
	printf (" [---------------<< Program starts >>---------------]\n");
	printf (" [                                                  ]\n");
	printf (" [    [+] Task: Create skimmed trees                ]\n");
	printf (" [    [+] List of parameters:                       ]\n");
	printf (" [     |-- Data type:           %s%*s]\n", str_dttype[isMC].data(),       20-len_dttype,  " ");
	printf (" [     |-- Reproccessing:       %s%*s]\n", str_reproc[reproc-1].data(),   20-len_reproc,  " ");
	printf (" [     |-- Lepton type:         %s%*s]\n", str_leptype[leptype-1].data(), 20-len_leptype, " ");
	printf (" [     |-- Year:                %d%*s]\n", year,                          16,             " ");
	printf (" [     `-- Number of files:     %02d%*s]\n", file2-file1+1,               18,             " ");
	//     (" [123456789 123456789 123456789 123456789 123456789 123456]\n");
	printf (" [                                                  ]\n");
	printf (" [--------------------------------------------------]\n");
	printf ("\n");

	// * Check the index of the file
	int   nFile       = list_nInput[leptype-1][year-2016];
	bool  valid_file1 = (file1<nFile+1) && (file1>0);
	bool  valid_file2 = (file2<nFile+1) && (file2>0);

	if (!valid_file1)
	{
		printf ("Error:\n");
		printf (" [!] First file [%d] is out of range [1,%d]\n", file1, nFile);
		printf ("  `-- Escape now\n");
		return 0;
	}

	if (!valid_file2)
	{
		printf (" Warning:\n");
		printf (" [!] Last file [%d] is out of range [1,%d]\n", file2, nFile);
		printf ("  `-- Exceeding file(s) will be ignored\n\n");
	}



	// + Loop over the files
	//----------------------
	printf (" Info: Main loop is starting\n");
	printf (" ---------------------------\n");
	for (int i=file1-1; i<file2; i++)
	{
		if (i > nFile-1)
		{
			printf (" [!] Warning:\n");
			printf ("  |-- Index [%d] is out of range ([1,%d])\n", i+1, nFile);
			printf ("  `-- Exiting loop\n\n");
			break;
		}

		bool   removepho   = list_infoInput[leptype-1][year-2016][i].rejpho;
		float  xsection    = list_infoInput[leptype-1][year-2016][i].xsec;
		string path_input  = list_infoInput[leptype-1][year-2016][i].path;
		string path_output = list_dirOutput[leptype-1][year-2016][i].path;

		printf (" [+] Start processing file #[%02d] in the list:\n", i+1);

		int status = CodeAna_Skim (isMC, xsection, removepho, reproc, year, path_input, path_output);
		printf ("\n");
	}

	return 0;
}
