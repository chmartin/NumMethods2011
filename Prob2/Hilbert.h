#ifndef HILBERT_H
#define HILBERT_H
 
class Hilbert
{

int dim;
MatDoub Matrix(int nn);
MatDoub Invert(int mm);

public:
Hilbert(int q);
MatDoub HilMatrix(){return Matrix(dim);}
MatDoub InvHilMat(){return Invert(dim);}

};

 
#endif