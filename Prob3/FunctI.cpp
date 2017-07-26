//Define a Functor I 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "FunctI.h"

Doub FunctI::operator() (double x)
{
	double tempExp = exp(-x);
	double tempAngle = 10.*x;
	double tempSin = sin(tempAngle);
	
	return (tempExp*pow(tempSin*tempSin, -1./3.));
}	