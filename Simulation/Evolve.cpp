//Personal Header for Evolving a set of masses in time

#include <stdlib.h>
#include <math.h>

#include "Evolve.h"

using namespace std;

void Evolve(int nMasses, double Mass[], double position[][3], double velocity[][3], double DeltaT)
{
	for(int i = 0; i < nMasses; i++)
	{
		//find acceleration of mass i
		double accel[3] = {0};
		
		//loop over other masses
		for(int j = 0; j < nMasses; j++)
		{
			if(i == j) continue;
			// calc |r| = sqrt(x^2+y^2+z^2)
			double r = sqrt( (position[i][0]-position[j][0])*(position[i][0]-position[j][0]) + (position[i][1]-position[j][1])*(position[i][1]-position[j][1]) + (position[i][3]-position[j][3])*(position[i][3]-position[j][3]));
			
			//gravitational softening a = 0 if r < .01
			if(r < 3.) continue;
			for(int k = 0; k < 3; k++)
			{
				// a_i =  sum_j(m_j*(x_j-x_i)/(r^3))
				accel[k] +=  Mass[j]*(position[j][k]-position[i][k])/(r*r*r);
			}
		}
		
		//pos = pos_old + vel_old*DeltaT + (DeltaT^2)*accel/2
		//vel = vel_old + accel*DeltaT
		for(int k = 0; k < 3; k++)
		{
			position[i][k] += velocity[i][k]*DeltaT + accel[k]*DeltaT*DeltaT/2.;
			velocity[i][k] += accel[k]*DeltaT;
		}
	}
			
}