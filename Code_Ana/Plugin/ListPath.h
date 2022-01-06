#ifndef LISTPATH_SKIM_H
#define LISTPATH_SKIM_H

#include <stdio.h>
#include <iostream>
#include <fstream>

#include "../Utility/fileBrowser.h"

using namespace std;


struct fInfo
{
	bool    rejpho;
	double  xsec;
	string  path;
};


vector<vector<vector<fInfo>>>  Fill_ListPath (int fileIO,  bool isMC,  vector<vector<int>>  &list_nPath,  int reproc,  int step)
{
	// + Define the vector
	//--------------------
	vector<vector<vector<fInfo>>>  list_full;
	vector<vector<fInfo>>  list_bytype;
	vector<fInfo>  list_byyear;

	// + Clean the lists
	//------------------
	// * String list
	list_full  . clear();

	// * Number list
	list_nPath . clear();


	// + Initiate list
	//----------------
	// * String lists
	for (int i=0; i<2; i++)
	{
		list_bytype . clear();

		for (int j=0; j<3; j++)
		{
			list_byyear . clear();
			list_bytype . push_back (list_byyear);
		}

		list_full . push_back (list_bytype);
	}
	//printf ("ok here 1\n");

	// * Number list
	list_nPath . assign (2, {0, 0, 0});
	//printf ("ok here 2\n");


	// * Get the list of file
	string procType[2] = {"DT", "MC"};
	string procStep[3] = {"Skim", "Preselect", "Select"};

	string namefile = "List_File/list";
	namefile += procType[isMC];
	namefile += (reproc==2) ? "UL" : "";
	namefile += (fileIO < 2) ? "_input" : "_output";
	namefile += procStep[step-1];
	namefile += ".txt";

	printf ("reading %s\n", namefile.data());

	std::ifstream file_list (namefile . data());

	string   str_line;
	int      rejPhoton;
	double   xsection;
	string   pathinput;
	TString  tpath;
	vector<string>  block;

	int  leptype;
	int  year;
	fInfo pathinfo;
	//printf ("ok here 3\n");

	string  lepSelect = (fileIO<2 && step==1) ? "DoubleMu" : "Muon";
	while (!file_list.eof())
	{
		std::getline (file_list, str_line);
		//printf ("   read: %s\n", str_line.data());

		if (str_line.length()==0)   continue;
		if (file_list.eof())   break;

		if (fileIO == 1)
		{
			block = Get_splittedString (str_line, "[ ]", true);
			pathinfo.rejpho = (atoi(block[0].data()) != 0);
			pathinfo.xsec   = atof(block[1].data());
			pathinfo.path   = block[2];
		}
		else
		{
			pathinfo.rejpho = 0;
			pathinfo.xsec   = 0.0;
			pathinfo.path   = str_line;
		}
		tpath = pathinfo.path;
		//printf ("[%d]  [%7f]  [%s]\n", pathinfo.rejpho, pathinfo.xsec, pathinfo.path.data());

		if (tpath.Length() < 1)   continue;

		year = 0;
		if (tpath.Contains("fall17_") || tpath.Contains("tree17") || tpath.Contains("2017"))   year = 1;
		else if (tpath.Contains("autumn18_") || tpath.Contains("tree18") || tpath.Contains("2018"))   year = 2;

		if (isMC && fileIO==1 && step==1)
		{
			list_full[0][year] . push_back (pathinfo);
			list_full[1][year] . push_back (pathinfo);
			continue;
		}

		leptype = (tpath . Contains(lepSelect.data())) ? 1 : 0;
		list_full[leptype][year] . push_back (pathinfo);
	}

	//printf ("ok here 4\n");
	file_list . close();

	for (int i=0; i<2; i++)
	{
		for (int j=0; j<3; j++)
		{
			list_nPath[i][j] = list_full[i][j] . size();
			//printf (" %d - %d: %d\n", i, j, list_nPath[i][j]);
		}
	}

	return  list_full;
}

#endif
