//Define a Functor 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "FuncI.h"

FuncI::FuncI(double pp)
{
	p = pp;
}

Doub FuncI::operator() (double x)
{
	
	return(sin(x)*cos(p*x));
}	