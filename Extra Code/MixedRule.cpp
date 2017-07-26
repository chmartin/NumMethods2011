//Define a Functor I 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "FunctI.h"
#include "MixedRule.h"

Doub MixedRule::operator() (double t)
{
	double x = exp(t-exp(-t));
	double dxdt = x*(1.+exp(-t));
	FunctI f_x_;
	return (f_x_(x)*dxdt);
}
