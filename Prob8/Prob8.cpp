//prob 8 for Num Methods
//Chris Martin

//includes
#include <nr3.h>
#include <eigen_sym.h>
#include <gaussj.h>
#include <eigen_unsym.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Print.h"
#include "InvIter.h"
#include "MatrixMult.h"

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob8-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Problem 8 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
		
		//define input
		double a[36] = {11, 2, 3, 1, 4, 2,
						 2, 9, 3, 5, 2, 1,
						 3, 3,15, 4, 3, 2,
						 1, 5, 4,12, 4, 3,
						 4, 2, 3, 4,17, 5,
						 2, 1, 2, 3, 5, 8};
		MatDoub A(6,6,a);
		
		//use householder on A
		Symmeig s(A);
		
		// read off eigenvalues and vectors from s
		ofile << "Here are the initial Eigenvalues." << endl;
		if(!Print(s.d, ofile).done)
		{
			cout << "Your output failed at eigenvalue vector." << endl;
			return 1;
		}
		
		ofile << "Here are the initial Eigenvectors. Each vector is a seperate column." << endl;
		if(!Print(s.z, ofile).done)
		{
			cout << "Your output failed at eigenvector matrix." << endl;
			return 1;
		}
		
		// refine eigenvalues via inverse iteration
		InvIter iter(A,s.d);
		VecDoub refinedvals = iter.RefinedVals;
		MatDoub refinedvecs = iter.RefinedVecs;
		
		ofile << "Here are the refined Eigenvalues." << endl;
		if(!Print(refinedvals, ofile).done)
		{
			cout << "Your output failed at refined vector." << endl;
			return 1;
		}
		ofile << "Here are the refined Eigenvectors. Each vector is a seperate column." << endl;
		if(!Print(refinedvecs, ofile).done)
		{
			cout << "Your output failed at eigenvector matrix." << endl;
			return 1;
		}
			
		ofile << endl << "Number 2" << endl;
		
		//Define A and B
		double a2[16] = {6,-4, 1, 0, 
						-4, 6,-4, 1,
						 1,-4, 6,-4,
						 0, 1,-4, 7};
		MatDoub A2(4,4,a2);
		
		double b2[16] = {1,-2, 3,-1,
		                -2, 6,-2, 3,
		                 3,-2, 6,-2,
		                -1, 3,-2, 9};
		MatDoub B2(4,4,b2);
		//replace B2 by its inverse and compute B^-1*A
		gaussj(B2);
		MatDoub No_2 = MatrixMult(B2, A2);
		ofile << "Here is the B^-1 * A matrix." << endl;
		if(!Print(No_2, ofile).done)
		{
			cout << "Your output failed at No_2 matrix." << endl;
			return 1;
		}
		
		Unsymmeig h(No_2, false);
		
		//pull the real componenets of the eigenvalues (drop complex)
		VecDoub initialvals(h.wri.size());
		for(int i = 0; i < h.wri.size(); i++)
		{
			initialvals[i] = h.wri[i].real();
		}
		
		ofile << "Here are the initial Eigenvalues." << endl;
		if(!Print(initialvals, ofile).done)
		{
			cout << "Your output failed at eigenvalue vector." << endl;
			return 1;
		}
		
		InvIter iter2(No_2,initialvals);
		VecDoub refinedvals2 = iter2.RefinedVals;
		MatDoub refinedvecs2 = iter2.RefinedVecs;
		
		ofile << "Here are the refined Eigenvalues." << endl;
		if(!Print(refinedvals2, ofile).done)
		{
			cout << "Your output failed at refined vector." << endl;
			return 1;
		}
		ofile << "Here are the refined Eigenvectors. Each vector is a seperate column." << endl;
		if(!Print(refinedvecs2, ofile).done)
		{
			cout << "Your output failed at eigenvector matrix." << endl;
			return 1;
		}
		
		ofile << endl << "Number 3" << endl;
		ofile << "See eigen_sym_Commented.h for the commented version."  << endl;
		
		ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}