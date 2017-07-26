//Define a Functor for Van der Pol Equation 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "Van_der_Pol.h"

Van_der_Pol::Van_der_Pol(double m)
{
	mu = m;
}

//follows form in ~17.0.4
void Van_der_Pol::operator() (const Doub t, VecDoub &x, VecDoub &dxdt)
{
	dxdt[0] = x[1];
	dxdt[1] = mu*(1-x[0]*x[0])*x[1]-x[0];
}