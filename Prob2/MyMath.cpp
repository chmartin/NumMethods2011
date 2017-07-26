//MyMath class
// Chris Martin

#include "MyMath.h"


double MyMath::factorial (int a, int stop)
{
	if (a > stop)
  	{
   		return (a * factorial ((a-1),stop));
	}
  	else
  	{
   		return 1.;
   	}
}

double MyMath::binom(int n, int k)
{
	if(n >= k && k >= 0)
	{
		return ( factorial(n,k) /(factorial(n-k)));
	}
	else
	{
		return 0.;
	}
}