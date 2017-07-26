//Define a Functor for Lane Emden Equation 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "Lane_Emden.h"

Lane_Emden::Lane_Emden(double m)
{
	n = m;
}

//follows form in ~17.0.4
void Lane_Emden::operator() (const Doub s, VecDoub &Psi, VecDoub &dPsi_ds)
{
	dPsi_ds[0] = Psi[1];
	dPsi_ds[1] = -3.*pow(Psi[0],n)-2.*Psi[1]/s;
}