//Matrix addition or subtraction
//Chris Martin

#include<nr3.h>
#include "MatrixAdd.h"

MatDoub MatrixAdd(MatDoub A, MatDoub B, bool subtract)
{
	MatDoub solution( max(A.nrows(), B.nrows()), max(A.ncols(), B.ncols()) );
	
	if(!subtract)
	{
		for(int i=0; i< solution.nrows(); i++)
		{
			for(int k=0; k< solution.ncols(); k++)
			{
				if (i< A.nrows() && i< B.nrows() && k < A.ncols() && k < B.ncols()) 
				{
					solution[i][k] = A[i][k]+B[i][k];
				}
				else if (i< A.nrows() && k < A.ncols() && (i >= B.nrows() || k >= B.ncols()))
				{
					solution[i][k] = A[i][k];
				}
				else if (i< B.nrows() && k < B.ncols() && (i >= A.nrows() || k >= A.ncols()))
				{
					solution[i][k] = B[i][k];
				}
				else
				{
					solution[i][k] = 0.;
				}
			}
		}
	}
	
	else
	{
		for(int i=0; i< solution.nrows(); i++)
		{
			for(int k=0; k< solution.ncols(); k++)
			{
				if (i< A.nrows() && i< B.nrows() && k < A.ncols() && k < B.ncols()) 
				{
					solution[i][k] = A[i][k]-B[i][k];
				}
				else if (i< A.nrows() && k < A.ncols() && (i >= B.nrows() || k >= B.ncols()))
				{
					solution[i][k] = A[i][k];
				}
				else if (i< B.nrows() && k < B.ncols() && (i >= A.nrows() || k >= A.ncols()))
				{
					solution[i][k] = B[i][k];
				}
				else
				{
					solution[i][k] = 0.;
				}
			}
		}
	}
	return solution;
}