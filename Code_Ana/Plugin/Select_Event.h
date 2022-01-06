#ifndef  SELECT_EVENT_H
#define  SELECT_EVENT_H


#include "../Utility/untuplizer_v09.h"
#include "../Utility/Calculator.h"

using namespace std;


//=========================
// + Selection at skim step
//=========================
bool  SelectEvent_Skim (TreeReader &tree_input,  int year)
{
	bool     isPVGood = tree_input . GetBool   ("isPVGood");
	Long64_t HLT      = tree_input . GetLong64 ("HLTEleMuX");

	bool passTrigger = (HLT>>5&1) || (HLT>>40&1) || (HLT>>15&1) || (HLT>>42&1)|| (HLT>>14&1) || (HLT>>41&1);
	if (year == 2017)   passTrigger = (HLT>>14&1) || (HLT>>40&1);
	else if (year == 2018)   passTrigger = (HLT>>15&1) || (HLT>>40&1);

	return (passTrigger && isPVGood);
}


//=======================
// + Selection at the end
//=======================
pair<int,tuple<int,int,int,int>>  SelectEvent_Final_Squeeze (TreeReader &tree_input, int region, int leptype)
{
	// + List of return values
	//------------------------
	pair<int,tuple<int,int,int,int>> result;

	int stt_Selection;
	tuple<int,int,int,int>  objID;

	int ilep1;
	int ilep2;
	int ipho;
	int ijet;

	double deltaR1;
	double deltaR2;
	double deltaR3;


	// + List of input
	//----------------
	// * Create an iterator
	vector<int>::iterator it;
	bool doAppend;

	// * Lepctron
	int    nLep;
	float *lepPt;
	float *lepEta;
	float *lepPhi;
	float *lepEn;
	int   *lepPass;

	if (leptype == 1)
	{
		nLep    = tree_input . GetInt      ("nEle");
		lepPt   = tree_input . GetPtrFloat ("eleCalibPt");
		lepEta  = tree_input . GetPtrFloat ("eleEta");
		lepPhi  = tree_input . GetPtrFloat ("elePhi");
		lepEn   = tree_input . GetPtrFloat ("eleCalibEn");
		lepPass = tree_input . GetPtrInt   ("elePass");
	}
	else
	{
		nLep    = tree_input . GetInt      ("nMu");
		lepPt   = tree_input . GetPtrFloat ("muCorPt");
		lepEta  = tree_input . GetPtrFloat ("muEta");
		lepPhi  = tree_input . GetPtrFloat ("muPhi");
		lepEn   = tree_input . GetPtrFloat ("muEn");
		lepPass = tree_input . GetPtrInt   ("muPass");
	}

	vector<int>  list_ilep;
	list_ilep . clear();
	list_ilep . push_back(0);

	int nLepPass = (lepPass[0]==1) ? 1 : 0;

	for (int i=1; i<nLep; i++)
	{
		doAppend = true;

		if (lepPass[i] != 0)   nLepPass ++;

		for (it=list_ilep.begin(); it<list_ilep.end(); it++)
		{
			if (lepPt[i]>lepPt[*it])
			{
				list_ilep . insert (it,i);
				doAppend = false;
				break;
			}
		}

		if (doAppend)   list_ilep . push_back (i);
	}

	if (nLepPass > 2)
	{
		objID = make_tuple (-1, -1, -1, -1);
		stt_Selection = 0;
		result = make_pair (stt_Selection, objID);

		return result;
	}

	// * Photon
	int    nPho                 = tree_input . GetInt      ("nPho");
	float *phoCalibEt           = tree_input . GetPtrFloat ("phoCalibEt");
	float *phoEta               = tree_input . GetPtrFloat ("phoEta");
	float *phoSCEta             = tree_input . GetPtrFloat ("phoSCEta");
	float *phoPhi               = tree_input . GetPtrFloat ("phoPhi");
	float *phoE                 = tree_input . GetPtrFloat ("phoE");
	float *phoPFChIso           = tree_input . GetPtrFloat ("phoPFChIso");
	float *phoPFPhoIso          = tree_input . GetPtrFloat ("phoPFPhoIso");
	float *phoSCEtaWidth        = tree_input . GetPtrFloat ("phoSCEtaWidth");
	float *phoR9                = tree_input . GetPtrFloat ("phoR9");
	float *phoSigmaIEtaIEtaFull = tree_input . GetPtrFloat ("phoSigmaIEtaIEtaFull");
	float *phoSigmaIEtaIPhiFull = tree_input . GetPtrFloat ("phoSigmaIEtaIPhiFull");
	float *phoE2x2Full          = tree_input . GetPtrFloat ("phoE2x2Full");
	float *phoE5x5Full          = tree_input . GetPtrFloat ("phoE5x5Full");
	int   *phoPass              = tree_input . GetPtrInt   ("phoPass");

	vector<int>  list_ipho;
	list_ipho . clear();
	list_ipho . push_back(0);

	for (int i=1; i<nPho; i++)
	{
		doAppend = true;

		for (it=list_ipho.begin(); it<list_ipho.end(); it++)
		{
			if (phoCalibEt[i]<phoCalibEt[*it])
			{
				list_ipho . insert (it,i);
				doAppend = false;
				break;
			}
		}

		if (doAppend)   list_ipho . push_back (i);
	}

	// * Jet
	int    nJet       = tree_input . GetInt      ("nJet");
	float *jetPt      = tree_input . GetPtrFloat ("jetPt");
	float *jetEta     = tree_input . GetPtrFloat ("jetEta");
	float *jetPhi     = tree_input . GetPtrFloat ("jetPhi");
	float *jetEn      = tree_input . GetPtrFloat ("jetEn");
	float *jetP4Smear = tree_input . GetPtrFloat ("jetP4Smear");
	int   *jetPass    = tree_input . GetPtrInt   ("jetPass");

	vector<int>  list_ijet;
	list_ijet . clear();

	int nJetPass = 0;

	if (nJet>0)
	{
		list_ijet . push_back(0);

		if (jetPass[0] == 1)   nJetPass ++;

		for (int i=1; i<nJet; i++)
		{
			doAppend = true;
			float jetPt1 = jetPt[i] * jetP4Smear[i];

			for (it=list_ijet.begin(); it<list_ijet.end(); it++)
			{
				float jetPt2 = jetPt[*it] * jetP4Smear[*it];

				if (jetPt1<jetPt2)
				{
					list_ijet . insert (it,i);
					doAppend = false;
					break;
				}
			}

			if (doAppend)   list_ijet . push_back (i);
			if (jetPass[i] == 1)   nJetPass ++;
		}
	}

	bool hasJet = (nJetPass > 0);


	// + Search for lepton pair
	//-------------------------
	vector<pair<int,int>>  list_pair;
	list_pair . clear();

	pair<int,int> pairID;
	TLorentzVector v4d_lep1;
	TLorentzVector v4d_lep2;
	TLorentzVector v4d_dilep;

	float dilepMass;
	bool  passPair;

	int lenLep = list_ilep.size();
	//for (int i=0; i<(lenLep-1); i++)
	for (int i=0; i<1; i++)
	{
		ilep1 = list_ilep[i];

		if (lepPass[ilep1]!=1  ||  lepPt[ilep1]<25)   continue;
		v4d_lep1 . SetPtEtaPhiE (lepPt[ilep1], lepEta[ilep1], lepPhi[ilep1], lepEn[ilep1]);

		for (int j=i+1; j<2; j++)
		{
			ilep2 = list_ilep[j];

			if (ilep1 == ilep2)   continue;

			if (lepPass[ilep2] != 1)   continue;
			v4d_lep2 . SetPtEtaPhiE (lepPt[ilep2], lepEta[ilep2], lepPhi[ilep2], lepEn[ilep2]);

			v4d_dilep = v4d_lep1 + v4d_lep2;
			dilepMass = v4d_dilep . M();

			passPair = dilepMass > 50;

			if (passPair)
			{
				pairID = make_pair (ilep1, ilep2);
				list_pair . push_back (pairID);
			}
		}
	}

	if (list_pair.size()<1)
	{
		stt_Selection = 0;
		objID = make_tuple (-1, -1, -1, -1);
		result = make_pair (stt_Selection, objID);

		return result;
	}


	// + Check the angle between lepctron and photon
	//----------------------------------------------
	vector<tuple<int,int,int>>  list_triplet;
	list_triplet . clear();

	tuple<int,int,int>  triplet;

	float isocut[2] = {1.5, 2.0};
	bool isEB;
	bool passIso;

	for (int i=0; i<int(list_pair.size()); i++)
	{
		ilep1 = list_pair[i] . first;
		ilep2 = list_pair[i] . second;

		//for (int j=0; j<int(list_ipho.size()); j++)
		for (int j=0; j<1; j++)
		{
			ipho = list_ipho[j];

			if (phoPass[ipho] != 1)   continue;

			isEB = abs(phoSCEta[ipho]) < 1.4442;

			passIso = (region == 0) ? phoPFChIso[ipho]<isocut[isEB] : phoPFChIso[ipho]>isocut[isEB];
			if (!passIso)   continue;

			deltaR1 = compute_DeltaR (lepEta[ilep1], phoEta[ipho], lepPhi[ilep1], phoPhi[ipho]);
			deltaR2 = compute_DeltaR (lepEta[ilep2], phoEta[ipho], lepPhi[ilep2], phoPhi[ipho]);

			if (deltaR1<0.7 || deltaR2<0.7)   continue;

			triplet = make_tuple (ilep1, ilep2, ipho);
			list_triplet . push_back (triplet);
		}
	}

	if (list_triplet.size()<1)
	{
		objID = make_tuple (-1, -1, -1, -1);
		stt_Selection = 0;
		result = make_pair (stt_Selection, objID);

		return result;
	}


	// + Check the angle between the jet and other objects
	//----------------------------------------------------
	ilep1 = get<0>(list_triplet[0]);
	ilep2 = get<1>(list_triplet[0]);
	ipho  = get<2>(list_triplet[0]);
	ijet  = -1;

	if (!hasJet)
	{
		objID = make_tuple (ilep1, ilep2, ipho, ijet);
		result = make_pair (1, objID);

		return result;
	}

	int ijettmp;

	for (int i=0; i<int(list_triplet.size()); i++)
	{
		ilep1 = get<0>(list_triplet[i]);
		ilep2 = get<1>(list_triplet[i]);
		ipho  = get<2>(list_triplet[i]);

		for (int j=0; j<int(list_ijet.size()); j++)
		{
			ijettmp = list_ijet[j];

			if (jetPass[ijettmp] != 1)   continue;

			deltaR1 = compute_DeltaR (jetEta[ijettmp], lepEta[ilep1], jetPhi[ijettmp], lepPhi[ilep1]);
			deltaR2 = compute_DeltaR (jetEta[ijettmp], lepEta[ilep2], jetPhi[ijettmp], lepPhi[ilep2]);
			deltaR3 = compute_DeltaR (jetEta[ijettmp], phoEta[ipho],  jetPhi[ijettmp], phoPhi[ipho]);

			if (deltaR1<0.4 || deltaR2<0.4 || deltaR3<0.4)   continue;

			ijet   = ijettmp;

			objID  = make_tuple (ilep1, ilep2, ipho, ijet);
			result = make_pair (1, objID);

			return result;
		}
	}

	ilep1 = get<0>(list_triplet[0]);
	ilep2 = get<1>(list_triplet[0]);
	ipho  = get<2>(list_triplet[0]);

	objID = make_tuple (ilep1, ilep2, ipho, ijet);
	result = make_pair (1, objID);

	return result;
}


#endif
