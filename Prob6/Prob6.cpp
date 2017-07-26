//prob 6 for Num Methods
//Chris Martin

//includes
#include <nr3.h>
#include <mins.h>
#include <mins_ndim.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Func.h"
#include "Print.h"
#include "Func2.h"
#include "Func3.h"

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob6-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Problem 6 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
		ofile << "The minimum using Powell's method starting at x=1, y=-1 is: " << endl;
		
		//define starting point
		double point[2] = {1,-1};
		VecDoub p(2,point);
		
		//define function and use powell method
		Func phi;
		Powell<Func> powell(phi);
		p=powell.minimize(p);
		ofile << "Here are the coordinates of your minimum, (x,y):" << endl;
		if(!Print(p, ofile).done)
			{
				cout << "Your output failed at p vector." << endl;
				return 1;
			}
		ofile << "Here the value of the function:" << powell.fret << endl;
		ofile << endl;
	
		ofile << "Number 2" << endl;
		ofile << "Use Golden method for min, and Romberg for integration." << endl;
		
		//define function (a function of p) and find minimum
		Func2 func2;
		Golden gold;
		gold.bracket(0,2,func2);
		double pmin = gold.minimize(func2);
		
		ofile << "The minimum is a p= " << pmin << endl;
		ofile << "The value of the integral is: " << gold.fmin << endl;
		ofile << endl;
	
		ofile << "Number 3" << endl;
		ofile << "Use Golden method for min." << endl;
		//define function (a function of sigma/r) and find minimum
		Func3 func3;
		Golden gold3;
		gold3.bracket(0,1,func3);
		double rmin = gold3.minimize(func3);
		
		ofile << "The minimum is a sigma/r= " << rmin << endl;
		ofile << "The value of the potential is: " << gold3.fmin << endl;
		ofile << endl;
	
		ofile << "Number 4" << endl;
		double x = 1;
		double y = 0;
		double step = 1e-5;
		ofile << "Minimized by brute force with a step size of " << step << endl;
		double phi4;
		double min = 100;
		double xmin, ymin;
		
		do
		{
			do
			{
		 		phi4 = (x-1)*(x-1)+(y-1)*(y-1);
				if(phi4 < min)
		 		{
		 			min = phi4;
		 			xmin = x;
		 			ymin = y;
		 		}
		 		y = y+step;
		 	}
		 	while(x+y <= 1);
		 	x=x-step;
		}
		while(x >= .6);
		ofile << "The minimum is at (x,y)= (" << xmin << ", " << ymin << ")" << endl;
		ofile << "The value of the function is: " << min << endl;
		
		
	ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	