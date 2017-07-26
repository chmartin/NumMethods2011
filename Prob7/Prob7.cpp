//prob 7 for Num Methods
//Chris Martin

//includes
#include <nr3.h>
#include <eigen_sym.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Print.h"

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob7-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Problem 7 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
		ofile << "See eigen_sym_Commented.h for the commented version." << endl << endl;
		
		ofile << "Number 2" << endl;
		
		double a[16] = {7,2,3,-1,2,8,5,1,3,5,12,9,-1,1,9,7};
		MatDoub A(4,4,a);
		
		//use householder on A
		Symmeig s(A);
		
		// read off eigenvalues and vectors from s
		ofile << "Here are the Eigenvalues." << endl;
		if(!Print(s.d, ofile).done)
			{
				cout << "Your output failed at eigenvalue vector." << endl;
				return 1;
			}
		
		ofile << "Here are the Eigenvectors. Each vector is a seperate column." << endl;
		if(!Print(s.z, ofile).done)
			{
				cout << "Your output failed at eigenvector matrix." << endl;
				return 1;
			}
			
		//reconstruct tridiagonal matrix from s and tred2
		MatDoub Tri(4,4,0.);
		
		s.z = A;
		s.tred2();
		for(int i = 0 ; i < 4; i++)
		{
			Tri[i][i] = s.d[i];
			
			Tri[i][i+1] =Tri[i+1][i] = s.e[i+1];
		}
			
		ofile << "Here is the Tridiagonal Matrix." << endl;
		if(!Print(Tri, ofile).done)
			{
				cout << "Your output failed at Tri matrix." << endl;
				return 1;
			}
		
		ofile << endl << "Number 3" << endl;
		ofile << "The proof can be found in Prob3.pdf. Or you can look through the LaTeX files..." << endl;
		
		
	ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	