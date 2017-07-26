//Define a Functor 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "Func.h"

Func::Func(double epsilon)
{
	eps = epsilon;
}

double Func::y(double x)
{
	return(1./(x*x+1.)-eps);
}

Doub Func::operator() (double x)
{
	
	return(2*y(x)-exp(-x+1.));
}	

Doub Func::df(double x)
{
   dy_dx = -(2*x)/((x*x+1.)*(x*x+1.));
   
   return(2*dy_dx+exp(-x+1.));
}