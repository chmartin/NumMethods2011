#ifndef L_E_H
#define L_E_H
 
class Lane_Emden
{
	private:
	Doub n;
	
	public:
	Lane_Emden(double m);
	void operator() (const Doub s, VecDoub &Psi, VecDoub &dPsi_ds);
};
 
#endif