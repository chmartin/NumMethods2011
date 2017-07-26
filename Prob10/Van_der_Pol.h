#ifndef VAN_H
#define VAN_H
 
class Van_der_Pol
{
	private:
	Doub mu;
	
	public:
	Van_der_Pol(double m);
	void operator() (const Doub t, VecDoub &x, VecDoub &dxdt);
};
 
#endif