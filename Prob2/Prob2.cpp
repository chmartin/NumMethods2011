/*Problems  2.
By Chris Martin

1.	Please write down a 10 x 15 matrix and use the Singular Value Decomposition (SVD) 
	given in the webnote 2. at  http://nr.com/webnotes/.

2.	Please write down a 10 x 10 band matrix and then invert it. Please now add a column 
	to the matrix and using the Sherman Morrison formula, please evaluate the matrix in 
	the quickest way.

3.	 Much, much harder. Please do not waste too much time on this one. Please write down
	a matrix of the form a_IJ = 1/(I + J+ 1) and invert. It is called a Hilbert matrix.
*/


//includes
#include <nr3.h>
#include <svd.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "RandList.h"
#include "MatrixMult.h"
#include "Scale.h"
#include "MatrixAdd.h"
#include "Transpose.h"
#include "Print.h"
#include "MyMath.h"
#include "Hilbert.h"

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob2-ChrisMartin.txt");
	if(ofile.is_open())
	{
	
		//text header
		ofile << "Prob 2 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << endl;
		
/*Please write down a 10 x 15 matrix and use the Singular Value Decomposition (SVD) 
	given in the webnote 2. at  http://nr.com/webnotes/. */
	
		ofile << "No. 1 " << endl;
		const int height = 10;
		const int width = 15;
		const int length = height*width;
		double a[length] = {0};
		
		//Randomize Array
		RandList( a, length );
		
		//print random array
		ofile << endl << "Here is your random matrix: " << endl;
		if(!Print(a, height, width, ofile).done)
		{
			cout << "Your output failed at random matrix." << endl;
			return 1;
		}
	
		//Pass to NR classes
		MatDoub OrigMatrix(height,width,a);
		
		//Pull U, V, and W from Matrix
		SVD SingValDcmp = SVD(OrigMatrix);
		MatDoub U = SingValDcmp.u;
		MatDoub V = SingValDcmp.v;
		VecDoub W = SingValDcmp.w;
		
		//print U
		ofile << endl << endl << "Here is U: " << endl;
		if(!Print(U, ofile).done)
		{
			cout << "Your output failed at U matrix." << endl;
			return 1;
		}
		
		//print V
		ofile << endl << "Here is V: " << endl;
		if(!Print(V, ofile).done)
		{
			cout << "Your output failed at V matrix." << endl;
			return 1;
		}
		
		//print W
		ofile << endl << "Here is W: " << endl;
		if(!Print(W, ofile).done)
		{
			cout << "Your output failed at W vector." << endl;
			return 1;
		}
		
		
/*Please write down a 10 x 10 band matrix and then invert it. Please now add a column 
	to the matrix and using the Sherman Morrison formula, please evaluate the matrix in 
	the quickest way.*/

		ofile << endl << "No 2. " << endl;
		
		//Random array
		const int height2 = 10;
		const int width2 = 10;
		const int length2 = height*width;
		double b[length2] = {0};
		
		//Randomize Array
		RandList( b, length2 );
		
		//print random
		ofile << endl << "Here is your random matrix: " << endl;
		if(!Print(b, height2, width2, ofile).done)
		{
			cout << "Your output failed at random matrix." << endl;
			return 1;
		}
		
		//Pass to NR classes
		MatDoub OrigMatrix2(height2,width2,b);
		
		//Pull U, V, and W from Matrix
		SVD SingValDcmp2 = SVD(OrigMatrix2);
		MatDoub U2 = SingValDcmp2.u;
		MatDoub V2 = SingValDcmp2.v;
		VecDoub W2 = SingValDcmp2.w;
		
		//Check condition number
		ofile << endl << endl << "Is this matrix invertable?" << endl;
		ofile << "It has an inverse condition number of: ";
		ofile << SingValDcmp2.inv_condition() << endl;
		ofile << "The precision you can handle is approx 10^-15 (from NR3)" << endl;
		if(SingValDcmp2.inv_condition() > pow(10.,-15.))
		{
			//compute 1/w matrix
			MatDoub InvW2(W2.size(), W2.size());
			for( int i=0; i<W2.size(); i++)
			{
				InvW2[i][i] = 1/(W2[i]);
			}
			
			//compute inverse via SVD
			MatDoub InvMatrix2 = MatrixMult(V2, MatrixMult(InvW2, Transpose(U2) ) );
			
			//print inverse
			ofile << endl << "Here is your SVD inverse matrix: " << endl;
			if(!Print(InvMatrix2, ofile).done)
			{
				cout << "Your output failed at InvMatrix2 matrix." << endl;
				return 1;
			}
			
			//check inverse
			MatDoub One = MatrixMult(InvMatrix2, OrigMatrix2);
			//Print solution
			ofile << endl << "Here is your ~unitary~ matrix: " << endl;
			if(!Print(One, ofile).done)
			{
				cout << "Your output failed at One matrix." << endl;
				return 1;
			}
			
						
			
			//Add raondom Column to OrigMatrix
			/* initialize random seed: */
			srand ( time(NULL) );
			double Identity[width2] = {0.};
			Identity[rand() % width2] = 1.;
			MatDoub vcol(1,width2,Identity);
			double uarr[height2] = {0.};
			
			
			//Randomize Array
			RandList( uarr, height2 );
			
			MatDoub urand(height2,1,uarr);
			
			ofile << endl << "Using the Sherman-Morrison formula..." << endl;
			ofile << "Here is the vector v: " << endl;
			if(!Print(vcol, ofile).done)
			{
				cout << "Your output failed at v vector." << endl;
				return 1;
			}
			ofile << endl << "Here is the vector u: " << endl;
			if(!Print(urand, ofile).done)
			{
				cout << "Your output failed at u vector." << endl;
				return 1;
			}
			
			//following Procedure outlined on pg 78 of Num Mthds
			MatDoub z = MatrixMult(InvMatrix2,urand);
			MatDoub f = MatrixMult(Transpose(InvMatrix2),Transpose(vcol));
			MatDoub lambdaish = MatrixMult(vcol, z);
			double lambda = lambdaish[0][0];
			
			//print intermediate parameters
			ofile << endl << "Here are the intermediate parameters: " << endl;
			ofile << "Frist lambda: " << endl;
			if(!Print(lambdaish, ofile).done)
			{
				cout << "Your output failed at Lambda." << endl;
				return 1;
			}	
			ofile << "Here is the vector z: " << endl;
			if(!Print(z, ofile).done)
			{
				cout << "Your output failed at z vector." << endl;
				return 1;
			}
			ofile << endl << "Here is the vector w: " << endl;
			if(!Print(f, ofile).done)
			{
				cout << "Your output failed at f vector." << endl;
				return 1;
			}
			
			//Now solve for the new inverse matrix
			MatDoub temp1 = MatrixMult(z,Transpose(f));
			ofile << endl << "Here is z*w^T: " << endl;
			if(!Print(temp1, ofile).done)
			{
				cout << "Your output failed at temp1." << endl;
				return 1;
			}	
			ofile << endl << "Here is z*w/(1+lambda): " << endl;
			MatDoub temp2 = Scale(1/(1+lambda), temp1 );
			if(!Print(temp2, ofile).done)
			{
				cout << "Your output failed at temp2." << endl;
				return 1;
			}
			
			MatDoub InvMatrix2prime = MatrixAdd(InvMatrix2, Scale(1/(1+lambda), MatrixMult(z,Transpose(f)) ) , true );
			ofile << endl << "Here is your InvPrime matrix: " << endl;
			if(!Print(InvMatrix2prime, ofile).done)
			{
				cout << "Your output failed at InvPrime matrix." << endl;
				return 1;
			}
			
		}
		else
		{
			ofile << "Your matrix is too singular to invert." << endl;
			ofile << "Going to No.3" << endl;
		}
		

/*	Much, much harder. Please do not waste too much time on this one. Please write down
	a matrix of the form a_IJ = 1/(I + J+ 1) and invert. It is called a Hilbert matrix.
*/
		ofile << endl << "No 3. " << endl; 
		
		//Choose a random dimension between 1 and 20 and make a Hilbert Matrix
		/* initialize random seed: */
		srand ( time(NULL) );
		int dim = (rand()%20)+1;
		MatDoub HilbertMatrix = Hilbert(dim).HilMatrix();
		ofile << endl << "Here is your Hilbert Matrix of random Dim from 1 to 20: " << endl;
		if(!Print(HilbertMatrix, ofile).done)
 			{
				cout << "Your output failed at Hilbert matrix." << endl;
 				return 1;
 			}
 			
 		ofile << endl << "Here is the analytical inverse from Wolframs Math World Formula: " << endl;
		if(!Print(Hilbert(dim).InvHilMat(), ofile).done)
 			{
				cout << "Your output failed at InvHilbert matrix." << endl;
 				return 1;
 			}
 			
 		//check inverse
		MatDoub HilOne = MatrixMult(HilbertMatrix, Hilbert(dim).InvHilMat());
		//Print solution
		ofile << endl << "Here is your ~unitary~ matrix: " << endl;
		if(!Print(HilOne, ofile).done)
		{
			cout << "Your output failed at HilOne matrix." << endl;
			return 1;
		}
 		
 		//find SVD inverse
		//Pull U, V, and W from Matrix
		SVD SingValDcmp3 = SVD(HilbertMatrix);
		MatDoub U3 = SingValDcmp3.u;
		MatDoub V3 = SingValDcmp3.v;
		VecDoub W3 = SingValDcmp3.w;
		
		//Check condition number
		ofile << endl << endl << "Is this matrix invertable?" << endl;
		ofile << "It has an inverse condition number of: ";
		ofile << SingValDcmp3.inv_condition() << endl;
		ofile << "The precision you can handle is approx 10^-15 (from NR3)" << endl;
		if(SingValDcmp3.inv_condition() > pow(10.,-15.))
		{
			//compute 1/w matrix
			MatDoub InvW3(W3.size(), W3.size());
			for( int i=0; i<W3.size(); i++)
			{
				InvW3[i][i] = 1/(W3[i]);
			}
			
			//compute inverse via SVD
			MatDoub InvMatrix3 = MatrixMult(V3, MatrixMult(InvW3, Transpose(U3) ) );
			
			//print inverse
			ofile << endl << "Here is your SVD inverse matrix: " << endl;
			if(!Print(InvMatrix3, ofile).done)
			{
				cout << "Your output failed at InvMatrix3 matrix." << endl;
				return 1;
			}
			
			//check inverse
			MatDoub HilOne2 = MatrixMult(InvMatrix3, HilbertMatrix);
			//Print solution
			ofile << endl << "Here is your ~unitary~ matrix: " << endl;
			if(!Print(HilOne2, ofile).done)
			{
				cout << "Your output failed at HilOne2 matrix." << endl;
				return 1;
			}
		}
		else
		{
			ofile << "Your matrix is too singular to invert." << endl;
			ofile << endl;
		}
 		
		
		
		ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	