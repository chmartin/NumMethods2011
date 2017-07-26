//Define a Functor 
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "Func.h"

Doub Func::operator() (VecDoub_I &x)
{
	
	return(100*(x[1]-x[0]*x[0])*(x[1]-x[0]*x[0])+(1-x[0])*(1-x[0]));
}	

