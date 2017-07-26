#ifndef INV_ITER_H
#define INV_ITER_H
 
class InvIter{
public:
	InvIter (MatDoub A, VecDoub eigenvals);
	VecDoub RefinedVals;
	MatDoub	RefinedVecs;
};

#endif