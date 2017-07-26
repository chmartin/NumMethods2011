//Generate a Hilbert Matrix
//Chris Martin

#include <nr3.h>
#include <math.h>
#include "Hilbert.h"
#include "MyMath.h"


Hilbert::Hilbert(int q)
{
 	dim = q;
}

MatDoub Hilbert::Matrix(int nn)
{
	MatDoub solution(nn,nn);
	
	for(int i=0; i< solution.nrows(); i++)
	{
		for(int k=0; k< solution.ncols(); k++)
		{
			solution[i][k] = 1./(i+1.+k);
		}
	}
	return solution;
}

MatDoub Hilbert::Invert(int mm)
{
	MatDoub invsolution(mm,mm);
	
	for(int i=0; i < invsolution.nrows(); i++)
	{
		for(int k=0; k < invsolution.ncols(); k++)
		{
			invsolution[i][k] = 
				pow(-1.,(i+k+2.))*(i+k+1.)*
				MyMath().binom((mm+i),(mm-k-1))*
				MyMath().binom((mm+k),(mm-i-1))*
				pow(MyMath().binom((i+k),i),2.);
		}
	}
	return invsolution;
}

