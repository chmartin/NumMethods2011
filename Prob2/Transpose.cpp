//Matrix Transpose
//Chris Martin

#include <nr3.h>
#include "Transpose.h"

MatDoub Transpose(MatDoub A)
{
	MatDoub solution(A.ncols(), A.nrows());
	
	for(int i=0; i< solution.nrows(); i++)
		{
			for(int k=0; k< solution.ncols(); k++)
			{
				solution[i][k] = A[k][i];
			}
		}
	return solution;
}