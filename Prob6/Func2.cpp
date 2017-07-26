//Define a Functor 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include <interp_1d.h>
#include <quadrature.h>
#include <romberg.h>

#include "Func2.h"
#include "FuncI.h"

const double PI = 3.141592;

Doub Func2::operator() (double p)
{
	//define integrand for this p
	FuncI integrand(p);
	//evaluate the integral (function of x)
	Midpnt<FuncI> q(integrand,0,PI);
	return(qromo(q));
}