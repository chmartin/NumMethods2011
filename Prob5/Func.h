#ifndef FUNC_H
#define FUNC_H
 
class Func
{
	private:
	double eps;
	double dy_dx;
	
	public:
	double y(double x);
	Func(double epsilon);
	Doub operator() (double x);
	Doub df(double x);

};

 
#endif