//Matrix * scalar
// Chris Martin

#include <nr3.h>
#include "Scale.h"

MatDoub Scale(double scale, MatDoub A)
{
	MatDoub solution(A.nrows(),A.ncols());
	
	for(int i=0; i< solution.nrows(); i++)
		{
			for(int k=0; k< solution.ncols(); k++)
			{
				solution[i][k] = scale*A[i][k];
			}
		}
	return solution;
}