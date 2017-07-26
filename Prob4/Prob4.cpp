//Prob 4 Num Methods 2012
//Chris Martin

/*

Find a Rational Function of degree 6 in the numerator and also degree 6 
in the denominator that best approximates the general hypergeometric 
function (see P318 formula (6.13.1) in Numerical Recipes) 
2F1 (1,2,1:z) in the range:

(1)	on the real axis in the range 0->1/2. 
	Compare the value of the approximation function and the value of the 
	hypergeometric function directly evaluated by the routine in 6.13 for
	z=1/2 and see how good the approximation is. 
(2)	on the real axis in the range 0->1 
	(Do not go too close to the branch point at x=1). 
	Again compare the values got by both methods and this time you need to
	find out how close to 1 z and be in order to make the two results agree
	with each other within some allowed error, say 1 percent of difference. 
(3)	Extra Credit: Find the general complex rational function approximation 
	for 0<|z| <1.
 */
 

//includes
#include <nr3.h>
#include <stepper.h>
#include <stepperbs.h>
#include <odeint.h>
#include <hypgeo.h>
#include <poly.h>
#include <svd.h>
#include <ratlsq.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include "Print.h"

using namespace std;

Doub HypGeo(Doub x)
{
	complex<double> a (1.,0.);
	complex<double> b (2.,0.);
	complex<double> c (1.,0.);
	complex<double> z (x,0.);
	return (hypgeo(a,b,c,z).real());
}	

int main()
{

	//make output file
	ofstream ofile ("Prob4-ChrisMartin.txt");
	if(ofile.is_open())
	{
	
	
		//text header
		ofile << "Prob 3 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
		
		// Number(1)
		// on the real axis in the range 0->1/2
		ofile << "No. 1" << endl;
		ofile << "Real axis on interval 0 to 1/2." << endl;
		
		//define the Hypergeometric funtor and the approximation
		Doub deviation;
		ofile << "Here is the value at 1/2 from hypgeo:" << endl;
		ofile << HypGeo(.5) << endl;

		Ratfn HalfApprox = ratlsq(HypGeo, 0.,.5,6,6,deviation);
		//Print the Approximation
		ofile << "Here are the coefficents of your approximation, (p_0,...,p_6,q_1,...,q_6):" << endl;
		if(!Print(HalfApprox.cofs, ofile).done)
			{
				cout << "Your output failed at cofs vector." << endl;
				return 1;
			}
		
		ofile << "Here is the value at 1/2 from the Approximation:" << endl;
		ofile << HalfApprox(.5) << endl;
		
		ofile << "Here is the deviation returnted by the approximation:" << endl;
		ofile << deviation << endl;
		
		ofile << "Percent deviation: " << endl;
		ofile << (HypGeo(.5)-HalfApprox(.5))/HypGeo(.5) << endl << endl;
		
		// Number(2)
		// on the real axis in the range 0->1
		Doub epsilon = 1.e-10;
		Doub real = 0;
		Doub approx = 0;
		int n = 1;
		Doub diff = 0;
		Doub percentdiff = 0;
		ofile << "No. 2" << endl;
		ofile << "Real axis on interval 0 to .9999+epsilon" << endl << endl;
		ofile << "The iterations are not what was aked for in the problem... here we go UP until" << endl;
		ofile << "we reach a reasonable agreement between the real and approx values." << endl;
		ofile << "The bottom up approach is necessitated by the error handeling precess in the" << endl;
		ofile << "Standard nr3 libraries. Here the maximum acceptable error between the approx and " << endl;
		ofile << "~real is 1e-10 percent." << endl;
		
		//loop until (deviation)/real < 1%
		do
		{

				real = HypGeo(.9999+epsilon*n);
			
				Ratfn OneApprox = ratlsq(HypGeo, 0.,.9999+epsilon*n,6,6,deviation);
		
			
				approx = OneApprox(.9999+epsilon*n);
			
				diff = abs(real-approx);
				percentdiff = diff/real;
			
				if(percentdiff < epsilon)
				{
					ofile << "Upper limit for this run is: " << .9999+epsilon*n << endl;
			
					//define the Hypergeometric funtor and the approximation
					ofile << "Here is the value at ~1 from hypgeo:" << endl;
					ofile << real << endl;
					
					ofile << "Here is the value at ~1 from the Approximation:" << endl;
					ofile << approx << endl;
					
					ofile << "Percent deviation: " << endl;
					ofile << percentdiff << endl << endl;
					
					//Print the Approximation
					ofile << "Here are the coefficents of your approximation, (p_0,...,p_6,q_1,...,q_6):" << endl;
					if(!Print(OneApprox.cofs, ofile).done)
					{
						cout << "Your output failed at cofs vector." << endl;
						return 1;
					}
					ofile << "Here is the deviation returnted by the approximation:" << endl;
					ofile << deviation << endl;
				}
			
			n++;
		}
		while(percentdiff > epsilon);
		

		
	ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	