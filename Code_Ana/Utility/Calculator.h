#ifndef CALCULATOR_H
#define CALCULATOR_H

using namespace std;


// + define the value for Pi
//==========================
double pival = 3.14159265358979323846;


// + Computation of delta Phi
//===========================
double compute_DeltaPhi (Float_t phi1, Float_t phi2)
{
	double subtraction = phi1 - phi2;
	double delPhi;

	if (abs(subtraction) > pival)   delPhi = 2*pival - abs(subtraction);
	else   delPhi = abs(subtraction);

	return delPhi;
}


// + Computation of delta R (eta, phi)
//====================================
double compute_DeltaR (double eta1, double eta2, double phi1, double phi2)
{
	// * Calculate deltaPhi
	double subtraction = phi1 - phi2;
	double delPhi;

	if (abs(subtraction) > pival)   delPhi = 2*pival - abs(subtraction);
	else   delPhi = abs(subtraction);


	// * Calculate delta eta
	double delEta = eta1 - eta2;


	// * Calculate deltaR
	double delR = sqrt (pow(delPhi,2) + pow(delEta,2));
	return delR;
}


// + Computation of delta R2 (theta, phi)
//=======================================
double compute_DeltaR2 (double theta1, double theta2, double phi1, double phi2)
{
	// * Calculate deltaPhi
	double dPhi = phi1 - phi2;
	double delPhi = 0;

	if (abs(dPhi) > pival)   delPhi = 2*pival - abs(dPhi);
	else   delPhi = abs(dPhi);


	// * Calculate delta theta
	double dTheta = theta1 - theta2;
	double delTheta = 0;

	if (abs(dTheta) > pival)   delTheta = 2*pival - abs(dTheta);
	else   delTheta = abs(dTheta);


	// * Calculate deltaR2
	double delR = sqrt (pow(delPhi,2) + pow(delTheta,2));
	return delR;
}




double compute_DeltaRnorm (double eta1, double eta2, double phi1, double phi2)
{
	// * define the value for Pi
	double pival = 3.14159265358979323846;


	// * Calculate deltaPhi
	double subtraction = phi1 - phi2;
	double delPhi;
	double normfactor = (abs(eta1) > abs(eta2)) ? abs(eta1) : abs(eta2);

	if (abs(subtraction) > pival)   delPhi = 2*pival - abs(subtraction);
	else   delPhi = abs(subtraction);


	// * Calculate normalized delta eta
	double delEta;
	if (normfactor == 0) delEta = abs(eta1 - eta2)/normfactor;
	else                 delEta = 0;


	// * Calculate deltaR
	double delR = sqrt (pow(delPhi,2) + pow(delEta,2));
	return delR;
}



#endif
