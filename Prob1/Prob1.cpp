// Let us begin!
/*

Construct your own 10 by 10 matrix and use LUdcmp program from Chapter 2 of 
	Numerical recipes or an equivalent program to reduce the matrix to LU form.
	
Solve for the inverse and check your solution  by claculating A A^(-1) =1.

Extra:   Make one line in the matrix equal to (1 + \epsilon} times another row.
See how small \epsilon can be before problems arise. [Incomplete]
*/

//includes
#include<nr3.h>
#include<ludcmp.h>
#include<iostream>
#include <stdlib.h>
#include<time.h>

int main()
{
	//Declare
	double a[100];
	double Random;

			/* initialize random seed: */
			srand ( time(NULL) );
	
	//fill array with random doubles and print to screen
	cout << "This is your random matrix" << endl;
	for(int i = 0; i<100; i++)
	{
			
			Random = (double)(rand()%100)/100;
			a[i] = Random;
			cout << a[i] << ", ";
			if(i>0 && i%9 == 0) cout << endl;
	}
	
	
	//Pass to NR classes
	MatDoub_I OrigMatrix(10,10,a);
	// get LU matrix
	MatDoub LU = LUdcmp(OrigMatrix).lu;
	// find inv via LU
	MatDoub Inv;
	LUdcmp(OrigMatrix).inverse(Inv);
	
	
	//print L
	cout << "Here is L: " << endl;
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if(j<i)
			{
				cout << LU[i][j] << ", ";
			}
			else
			{
				cout << "0, ";
			}
		}
		cout << endl;
	}
	
	
	//print U
	cout << "Here is U: " << endl;
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if(j>=i)
			{
				cout << LU[i][j] << ", ";
			}
			else
			{
				cout << "0, ";
			}
		}
		cout << endl;
	}
	
	//print Inverse
	cout << "Here is the inverse: " << endl;
	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			cout << Inv[i][j] << ", ";
		}
		cout << endl;
	}
	
	// check inverse
	cout << "Did it work? (a*a^-1 ?=? 1)" << endl;
	double I[10][10] = {0};
	
	for(int i=0; i<10; i++)
	{
		for(int k=0; k<10; k++)
		{
			for(int j=0; j<10;j++)
			{
				I[i][k] += OrigMatrix[i][j]*Inv[j][k];
			}
			cout.setf(ios_base::fixed);
			cout << I[i][k] << ", ";
		}
		cout << endl;
	}

	return 0;
}