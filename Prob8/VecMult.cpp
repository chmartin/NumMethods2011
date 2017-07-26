//Vector multiplication function
//Chris Martin

#include <nr3.h>

#include "VecMult.h"

double VecMult(VecDoub A, VecDoub B)
{
	double solution = 0;
	if(A.size() == B.size())
	{
		for(int i = 0; i < B.size(); i++)
		{
			solution += A[i]*B[i];
		}
	}
	return solution;
}