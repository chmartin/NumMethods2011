//Define a Functor For the Real part of HypGeo 
//Chris Martin

#include <nr3.h>
#include <hypgeo.h>
#include <math.h>
#include "HypGeo.h"

Doub HypGeo::operator() (Doub z)
{
	
	return (hypgeo((1,0),(2,0),(1,0),(z,0)).real());
}	