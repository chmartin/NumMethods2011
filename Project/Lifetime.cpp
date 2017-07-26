//Find lifetime given tau
//Chris Martin
//

#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>

#include "Lifetime.h"

using namespace std;

double Lifetime(double tau)
{
	double t;
	
	double r = rand();
	t = -tau*log(1.-r/RAND_MAX);
	return(t);
};