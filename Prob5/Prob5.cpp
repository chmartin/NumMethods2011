//Example for Num Methods
//Chris Martin

//includes
#include <nr3.h>
#include <poly.h>
#include <mins.h>
#include <roots.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "Func.h"

using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Prob5-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Problem 5 NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
		ofile << "I have used the minimization method because the function is semipositive definite." << endl;
	
		//polynomial functor of form recomended on page 202
		//Define Vector of Coefficients
		double coeff_array[5] = {0.3136,-1.680,3.37,-3.0,1};
		VecDoub coeff_VecDoub(5, coeff_array);
	
		/* ALTERNATIVE DEF
		VecDoub coeff_VecDoub(4, {0.3136,-1.680,3.37,-3.0,1.});
		*/
	
		Poly F_x_ = Poly(coeff_VecDoub);
	
		//Send Polynomial F_x_ to Golden method and find root in (.67 to .73)
		//Need minimum because F_x_ is semipositive definite
		double lower1 = .67;
		double upper1 = .73;
		Golden golden;
		golden.bracket(lower1,upper1,F_x_);
		double root1 = golden.minimize(F_x_);
	
		ofile << "The Minimum between .67 and .73 is x = " << root1 << endl;
		ofile << "As a check, the function has a value of: " << golden.fmin << endl;
	
	
		//Send Polynomial F_x_ to Golden method and find root in (.78 to .83)
		//Need minimum because F_x_ is semipositive definite
		double lower2 = .78;
		double upper2 = .83;
		Golden golden2;
		golden2.bracket(lower2,upper2,F_x_);
		double root2 = golden2.minimize(F_x_);
	
		ofile << "The Minimum between .78 and .83 is x = " << root2 << endl;
		ofile << "As a check, the function has a value of: " << golden2.fmin << endl;
		
		ofile << endl << "Number 2" << endl;
		ofile << "The set has no roots when epsilon >= .034499." << endl;
		ofile << "The roots when epsilon = .034498 (critical value) are: (y,x)" << endl;
		Func f_x_(.034498);
		double root21 = rtnewt(f_x_,3.60,3.62,1e-5);
		ofile << f_x_.y(root21) << ", " << root21 << endl;
		double root22 = rtnewt(f_x_,3.62,3.64,1e-5);
		ofile << f_x_.y(root22) << ", " << root22 << endl;
		ofile << "The function continues to have 2 solutions while epsilon > 0." << endl;
		ofile << "The root when epsilon = 0 (critical value) is: (y,x)" << endl;
		Func f_x_2(0);
		double root23 = rtnewt(f_x_2,.99,1.05,1e-5);
		ofile << f_x_2.y(root23) << ", " << root23 << endl;
		ofile << "The function continues to have 1 solution while epsilon < 0." << endl;
	
	ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	