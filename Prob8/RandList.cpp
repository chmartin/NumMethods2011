//Personal Header for Random array

#include<time.h>
#include <stdlib.h>

#include "RandList.h"

using namespace std;

void RandList(double array[], int length)
{
	double random;
		
	/* initialize random seed: */
	srand ( time(NULL) );
	
	//fill array with random doubles 
	for(int i = 0; i<length; i++)
	{		
		random = (double)(rand()%100)/10;
		array[i] = random;
	}
}
	