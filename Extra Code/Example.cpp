//Example for Num Methods
//Chris Martin

//includes
#include <nr3.h>
#include <poly.h>
#include <roots.h>

#include <iostream>
#include <fstream>
#include <stdlib.h>


using namespace std;

int main()
{

	//make output file
	ofstream ofile ("Example-ChrisMartin.txt");
	if(ofile.is_open())
	{
		//text header
		ofile << "Example NumMthds Sp2012" << endl;
		ofile << "By: Chris Martin" << endl;
		ofile << std::setprecision(std::numeric_limits<double>::digits10+2);
		ofile << endl;
	
		ofile << "Number 1" << endl;
	
		//polynomial functor of form recomended on page 202
		//Define Vector of Coefficients
		double coeff_array[4] = {2.,-3,-3,2};
		VecDoub coeff_VecDoub(4, coeff_array);
	
		/* ALTERNATIVE DEF
		VecDoub coeff_VecDoub(4, {0.3136,-1.680,3.37,-3.0,1.});
		*/
	
		Poly F_x_ = Poly(coeff_VecDoub);
	
		//Send Polynomial F_x_ to Brent's method and find root in (-1.2 to -.8)
		double lower1 = -1.2;
		double upper1 = -.8;
		double epsilon = 1e-5;
		double root1 = zbrent<Poly> (F_x_, lower1, upper1, epsilon);
	
		ofile << "The First root is x = " << root1 << endl;
	
	
		//Send Polynomial F_x_ to Brent's method and find root in (.25-.75)
		double lower2 = .25;
		double upper2 = .75;
		double root2 = zbrent<Poly> (F_x_, lower2, upper2, epsilon);
	
		ofile << "The Second root is x = " << root2 << endl;
		
		//Send Polynomial F_x_ to Brent's method and find root in (1.75-2.25)
		double lower3 = 1.75;
		double upper3 = 2.25;
		double root3 = zbrent<Poly> (F_x_, lower3, upper3, epsilon);
	
		ofile << "The Third root is x = " << root3 << endl;
		
		ofile << endl << "Number 2" << endl;
	
	ofile.close();	
	}
	else cout << "Unable to open file";

	return 0;
}	