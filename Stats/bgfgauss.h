#ifndef BG_GAUSS_H
#define BG_GAUSS_H
 
void bgfgauss(const Doub x, VecDoub_I &a, Doub &y, VecDoub_O &dyda)
{
	fgauss(x, a, y, dyda);
   			
   	//add in background
   	y += 1.;
}
 
#endif