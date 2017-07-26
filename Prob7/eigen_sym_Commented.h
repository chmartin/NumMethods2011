//This is the commented version of the Householder method
//Chris Martin

//all equations from Num Recipies version 3

void Symmeig::tred2()
{
	Int l,k,j,i;
	Doub scale,hh,h,g,f;
	for (i=n-1;i>0;i--) {
		l=i-1;
		h=scale=0.0;
		if (l > 0) {
			for (k=0;k<i;k++)
			// this is Equation 11.3.17
				scale += abs(z[i][k]);
			if (scale == 0.0) // skip transform if scale is too small
				e[i]=z[i][l];
			else {
				for (k=0;k<i;k++) {
					z[i][k] /= scale; //this is equation 11.3.18
					h += z[i][k]*z[i][k]; // 11.3.16 h=sigma/scale^2
				}
				f=z[i][l];
				g=(f >= 0.0 ? -sqrt(h) : sqrt(h)); // g=sqrt(sigma)/scale
				e[i]=scale*g;
				h -= f*g; // h = sigma - a_il * sqrt(sigma)/scale
				// using the form of u given in 11.3.14 plugged into 11.3.4 
				// H = sigma - a_il*sqrt(sigma)
				z[i][l]=f-g; // a_il_new = a_il - sqrt(sigma)/scale
				// u is stored in row i of z in the form given in 11.3.14
				f=0.0;
				for (j=0;j<i;j++) {
					if (yesvecs)
						z[j][i]=z[i][j]/h; // u/H stored in column i of z
					g=0.0; // reset g
					for (k=0;k<j+1;k++)
						g += z[j][k]*z[i][k];
					for (k=j+1;k<i;k++)
						g += z[k][j]*z[i][k]; // g = A * u
					e[j]=g/h; // in unused elements of e store p in form 11.3.10
					f += e[j]*z[i][j];  // f = u*p
				}
				hh=f/(h+h); // 11.3.11 form K
				for (j=0;j<i;j++) { //form q and store in e
					f=z[i][j];
					e[j]=g=e[j]-hh*f;
					for (k=0;k<j+1;k++)
						z[j][k] -= (f*e[k]+g*z[i][k]); // write A' in A in form 11.3.13
				}
			}
		} else
			e[i]=z[i][l];
		d[i]=h;
	}
	if (yesvecs) d[0]=0.0;
	e[0]=0.0;
	for (i=0;i<n;i++) {
		if (yesvecs) {
			if (d[i] != 0.0) {
				for (j=0;j<i;j++) {
					g=0.0;
					for (k=0;k<i;k++)  // form P * Q
						g += z[i][k]*z[k][j];
					for (k=0;k<i;k++)
						z[k][j] -= g*z[k][i];
				}
			}
			d[i]=z[i][i];
			z[i][i]=1.0;
			for (j=0;j<i;j++) z[j][i]=z[i][j]=0.0;
		} else {
			d[i]=z[i][i];
		}
	}
}
