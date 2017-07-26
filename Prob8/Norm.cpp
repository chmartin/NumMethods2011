//Normalize vector function
//Chris Martin

#include <math.h>

#include <nr3.h>

#include "Norm.h"

#include "VecMult.h"

VecDoub Norm(VecDoub B)
{
	double scale = sqrt(abs(VecMult(B,B)));
	
	VecDoub Normed(B.size());
	for(int i = 0; i < B.size(); i++)
	{
		Normed[i] = B[i]/scale;
	}

	return Normed;
}