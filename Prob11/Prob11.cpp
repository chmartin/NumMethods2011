//prob 11 for Num Methods
//Chris Martin

//includes
#include <nr3.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob11-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Problem 11 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
		
		
		
	ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	