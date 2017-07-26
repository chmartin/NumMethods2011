//Inverse Iteration of Eigenvalues
//Chris Martin

#include <math.h>

#include <nr3.h>
#include <ludcmp.h>

#include "RandList.h"
#include "Norm.h"
#include "MatrixAdd.h"
#include "Scale.h"
#include "VecMult.h"
#include "VecAdd.h"

#include "InvIter.h"

VecDoub RefinedVals;
MatDoub	RefinedVecs;

InvIter::InvIter(MatDoub A, VecDoub eigenvals)
{
	
	RefinedVals.resize(eigenvals.size());
	RefinedVecs.resize(A.nrows(),A.ncols());
	
	//Create Identity Matrix
	MatDoub Ident(A.nrows(), A.ncols(), 0.);
	for(int i = 0; i < Ident.nrows(); i++)
	{
		Ident[i][i] = 1.;
	}
	
	
	for(int i = 0; i < eigenvals.size(); i++)
	{
		//set tau to initial guesses for eigenvalue
		double tau = eigenvals[i];
		
		
		VecDoub B(A.ncols(),0.), B_new(A.ncols(),0.);
		//iterate until abs(Bnew - Bold) < 1e-5
		do
		{
			B = B_new;
			//create normalized random vector
			double b[A.ncols()];
			RandList(b,A.ncols());
			VecDoub Braw(A.ncols(), b), y(A.ncols());
			B = Norm(Braw);
		
			//define the LHS of 11.8.6
			MatDoub Aish = MatrixAdd(A,Scale(tau,Ident),true);
			
			// do LU decomp on Eq 11.8.6
			LUdcmp alu(Aish);
			alu.solve(B,y);
		
			//set new B's 11.8.9 and Tau's 11.8.10
			B_new = Norm(y); 
			tau += 1./VecMult(B,y);
			
		}
		while(sqrt(abs(VecMult(VecAdd(B_new,B,true),VecAdd(B_new,B,true)))) <= 1e-5);
		
		//set to refined value
		RefinedVals[i] = tau;
		for(int j = 0; j < B_new.size(); j++)
		{
			RefinedVecs[j][i] = B_new[j];
		}
		
	}
				
}