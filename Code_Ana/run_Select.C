#include <stdio.h>
#include <iostream>

#include "Utility/untuplizer_v09.h"

#include "Plugin/ListPath.h"

#include "CodeAna_Select.C"


int  run_Select (bool isMC=0,  int reproc=1,  int year=2016,  int leptype=1,  int file1=1,  int file2=1)
{
	// + Create the list
	//------------------
	vector<vector<int>>  list_nInput;
	list_nInput . clear();
	vector<vector<vector<fInfo>>>  list_infoInput = Fill_ListPath (1, isMC, list_nInput, reproc, 3);


	// + Welcome messages
	//-------------------
	// * Check the parameters
	bool  valid_year     = year>2015 && year<2019;
	bool  valid_leptype  = leptype>0 && leptype<3;
	bool  valid_filetype = isMC==0 || isMC==1;
	bool  valid_para     = valid_year && valid_leptype && valid_filetype;

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
		if (!valid_filetype)
		{
			printf (" [!] File type's boolean value [%d] is invalid, must be 0(false) or 1(true)\n", isMC);
		}
		printf (" [!] Escape now\n");
		return 0;
	}

	// * Print welcome message if all are ok
	string str_dttype[2]  = {"Data", "MC"};
	string str_leptype[2] = {"electron", "muon"};

	int len_dttype  = str_dttype[isMC]  . length();
	int len_leptype = str_leptype[leptype-1] . length();

	printf ("\n");
	printf (" [---------------<< Program starts >>---------------]\n");
	printf (" [                                                  ]\n");
	printf (" [    [+] Task: Create trees of preselection        ]\n");
	printf (" [    [+] List of parameters:                       ]\n");
	printf (" [     |-- Data type:           %s%*s]\n", str_dttype[isMC].data(),       20-len_dttype,  " ");
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

	string nameRegion[2] = {"Signal", "Sideband"};

	for (int i=file1-1; i<file2; i++)
	{
		for (int reg=0; reg<2; reg++)
		{
			if (i > nFile-1)
			{
				printf (" [!] Warning:\n");
				printf ("  |-- Index [%d] is out of range ([1,%d])\n", i+1, nFile);
				printf ("  `-- Exiting loop\n\n");
				break;
			}

			string path_input  = list_infoInput[leptype-1][year-2016][i].path;
			printf (" [+] Start processing file #[%02d] for the [%s] region:\n", i+1, nameRegion[reg].data());

			int status = CodeAna_Select (isMC, year, reproc, leptype, path_input, reg);
			printf ("\n");
		}
	}

	return 0;
}
