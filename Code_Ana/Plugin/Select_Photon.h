#ifndef SELECT_PHOTON_H
#define SELECT_PHOTON_H




// + Skim photon
//==============
bool  SelectPhoton_Skim (TreeReader &tree_input)
{
	int    nPho;
	float *phoSCEta;
	int    nPhoPass = 0;
	bool   passPho;
	float  pEta;

	nPho     = tree_input . GetInt      ("nPho");
	phoSCEta = tree_input . GetPtrFloat ("phoSCEta");

	for (int i=0; i<nPho; i++)
	{
		pEta = abs (phoSCEta[i]);

		passPho = (pEta<1.4442 || (pEta<2.5 && pEta>1.566));

		if (passPho)   nPhoPass ++;
	}

	return (nPhoPass > 0);
}



#endif
