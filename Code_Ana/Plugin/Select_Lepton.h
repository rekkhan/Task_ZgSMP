#ifndef SELECT_LEPTON_H
#define SELECT_LEPTON_H




//==============
// + Skim lepton
//==============
bool SelectLepton_Skim (TreeReader &tree_input)
{
	int    nEle;
	int    nMu;
	float *eleSCEta;
	float *muEta;

	nEle     = tree_input . GetInt      ("nEle");
	nMu      = tree_input . GetInt      ("nMu");
	eleSCEta = tree_input . GetPtrFloat ("eleSCEta");
	muEta    = tree_input . GetPtrFloat ("muEta");

	int    nElePass = 0;
	int    nMuPass  = 0;
	bool   passEle = false;
	bool   passMu  = false;
	float  eEta;
	float  mEta;

	for (int i=0; i<nEle; i++)
	{
		eEta = abs(eleSCEta[i]);

		passEle = (eEta<1.4442 || (eEta>1.566 && eEta<2.4));
		if (passEle)   nElePass ++;
	}

	for (int i=0; i<nMu; i++)
	{
		mEta = abs(muEta[i]);

		passMu = (mEta < 2.4);
		if (passMu)   nMuPass ++;
	}

	return ((nElePass>1) || (nMuPass>1));
}


#endif
