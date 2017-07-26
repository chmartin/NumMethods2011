//Prob 3 Num Methods 2012
//Chris Martin

/*Please integrate:

I = ∫ dx Exp[-x]*(Sin[10x]^2)^(-1/3) 
over the range from 0 to b where b is as large as you can compute (b can be infinity in principle).

(1)	Use constant step h
(2)	Use Gaussian Quadrature
(3)	Challenge: If you like try making your own orthogonal polynomials
(4)	Iterate using methods (1) and (2) and try to get as high an accuracy as possible 
	(in certain limits it is quite a challenge)
 */

//includes
#include <nr3.h>
#include <quadrature.h>
#include <interp_1d.h>
#include <romberg.h>
#include <qgaus.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "FunctI.h"

#define PI 3.14159265

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob3-ChrisMartin.txt");
	if(ofile.is_open())
	{
	
		//text header
		ofile << "Prob 3 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
		
		//set precision used
		const double epsilon = 1e-100;
		ofile << "For this run epsilon = " << epsilon << endl;
		ofile << "This is used to set cutoffs on number of evaluations." << endl << endl;
		
		// (1)	Use constant step h
		ofile << "No. 1 (constant step h)" << endl << endl;
		ofile << "Integral cut at sqrt(n*pi)/10 for singularities." << endl;
		ofile << "If a piece between two cuts is big enough add it to integral." << endl;
		
		// this functor has a singularity every time n*pi = (10x)
		// variables for const step
		double min = 0; 
		double max;
		int n = 1;
		double integral = 0;
		double last = 0;
		double change;
		double addition = 0.;
		
		
		do
		{
			max = n*PI/10;
			//define f(x) 
			FunctI Integrand;
			//use Midpnt 
			Midpnt<FunctI> q(Integrand,min,max);
			addition = 0.;
			for(int j=0; j < 15; j++)
			{
				change = q.next();
				//check if this piece is big enough to matter
				if(j > 5 && (abs(change-addition) < abs(addition)*epsilon))
				{
					break;
				}
				addition = change;

			}		

			last = integral;
			integral += addition;
			min = max;
			n++;
		}
		while(n <= 5 || (abs(integral-last) > abs(last)*epsilon));
		
		ofile << "The number of pieces used in the integration was: " << (n-2) << endl;
		ofile << "Above a value of x=" << sqrt(n-2.)*sqrt(PI)/10.;
		ofile << " The pieces of the integral were too small." << endl;
		ofile << "The integral was evaluated over a range: t=0-"<< sqrt(n-2.)*sqrt(PI)/10. << endl;
		ofile << "The value of the integral is: " << integral << endl;
		
		// (2)	Use gaussian step h
		ofile << endl <<"No. 2 (Gaussian)" << endl << endl;
		ofile << "Integral cut at sqrt(n*pi)/10 for singularities." << endl;
		ofile << "If a piece between two cuts is big enough add it to integral." << endl;
		
		//variables for gauss
		double gmin = 0; 
		double gmax;
		int gn = 1;
		double gintegral = 0;
		double glast = 0;
		double gchange;
		double gaddition = 0.;
		
		do
		{	
			gmax = gn*PI/10;
			//define f(x) 
			FunctI gIntegrand;
			//use qgaus
			gaddition = 0.;
			gchange = qgaus(gIntegrand,gmin,gmax);
			if(abs(gchange-gaddition) < abs(gaddition)*epsilon)
			{
				ofile << "The " << gmin << "to " << gmax << " piece was skipped." << endl;
				goto gnext;
			}
			gaddition = gchange;	
			
			gnext:
			glast = gintegral;
			gintegral += gaddition;
			gmin = gmax;
			gn++;
		}
		while(gn <= 5 || (abs(gintegral-glast) > abs(glast)*epsilon));
		
		ofile << "The number of pieces used in the integration was: " << (gn-2) << endl;
		ofile << "Above a value of x=" << sqrt(gn-2.)*sqrt(PI)/10.;
		ofile << " The pieces of the integral were too small." << endl;
		ofile << "The integral was evaluated over a range: t=0-"<< sqrt(gn-2.)*sqrt(PI)/10. << endl;
		ofile << "The value of the integral is: " << gintegral << endl;
		
		ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	