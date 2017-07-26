//Matrix multiplication function
//Chris Martin

#include <nr3.h>
#include <iostream>
#include "MatrixMult.h"

MatDoub MatrixMult(MatDoub A, MatDoub B)
{
	MatDoub solution(A.nrows(), B.ncols());
	if(A.ncols() == B.nrows())
	{
		for(int i=0; i< solution.nrows(); i++)
		{
			for(int k=0; k< solution.ncols(); k++)
			{
				for(int j=0; j< A.ncols();j++)
				{
					solution[i][k] += A[i][j]*B[j][k];
				}
			}
		}
	}
	
	return solution;
}