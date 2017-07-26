//Universal Print class
//Chris Martin

using namespace std;

#include <fstream>
#include <nr3.h>
#include <stdlib.h>
#include "Print.h"

bool done = false;

Print::Print(MatDoub Matrix, ofstream& file) {
	if(file.is_open())
	{
		for(int i=0; i<Matrix.nrows(); i++)
		{
			for(int j=0; j<Matrix.ncols(); j++)
			{
				file << Matrix[i][j] << ", ";
			}
			file << endl;
		}
		done = true;
	}
}

Print::Print(VecDoub Vector, ofstream& file) {
	if(file.is_open())
	{
		for(int i=0; i<Vector.size(); i++)
		{
					file << Vector[i] << endl;
		}
		done = true;
	}
}

Print::Print(VecComplex Vector, ofstream& file) {
	if(file.is_open())
	{
		for(int i=0; i<Vector.size(); i++)
		{
					file << Vector[i] << endl;
		}
		done = true;
	}
}

Print::Print(double array[], const int height, const int width, ofstream& file) {
	int length = height*width;
	if(file.is_open())
	{
		for (int i=0; i<length; i++) 
		{
		 	if(i%(width) == 0) file << endl;
			file << array[i] << ", ";
			
		}
		done = true;
	}
}