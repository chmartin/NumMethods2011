//Vector addition or subtraction
//Chris Martin

#include<nr3.h>
#include "VecAdd.h"

VecDoub VecAdd(VecDoub A, VecDoub B, bool subtract)
{
	VecDoub solution(max(A.size(), B.size()));
	
	if(!subtract)
	{
		for(int i=0; i< solution.size(); i++)
		{
			if (i< A.size() && i< B.size()) 
			{
				solution[i] = A[i]+B[i];
			}
			else if (i< A.size() && i >= B.size())
			{
				solution[i] = A[i];
			}
			else if (i< B.size() && i >= A.size())
			{
				solution[i] = B[i];
			}
			else
			{
				solution[i] = 0.;
			}
		}
	}
	
	else
	{
		for(int i=0; i< solution.size(); i++)
		{
			if (i< A.size() && i< B.size()) 
			{
				solution[i] = A[i]+B[i];
			}
			else if (i< A.size() && i >= B.size())
			{
				solution[i] = A[i];
			}
			else if (i< B.size() && i >= A.size())
			{
				solution[i] = B[i];
			}
			else
			{
				solution[i] = 0.;
			}
		}
	}
	
	return solution;
}