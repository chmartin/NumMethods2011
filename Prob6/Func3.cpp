//Define a Functor 
//Chris Martin

#include <nr3.h>
#include <math.h>

#include "Func3.h"

Doub Func3::operator() (double r)
{
	return(4.*(pow(r,12.)-pow(r,6.)));
}