void Symmeig::tqli()
{
	Int m,l,iter,i,k;
	Doub s,r,p,g,f,dd,c,b;
	const Doub EPS=numeric_limits<Doub>::epsilon();
	for (i=1;i<n;i++) e[i-1]=e[i];  //Renumber off diagonal elements
	e[n-1]=0.0;
	for (l=0;l<n;l++) {
		iter=0;
		do {
			for (m=l;m<n-1;m++) {				//search for small subdiagonal element to split
				dd=abs(d[m])+abs(d[m+1]);		//matrix and use the implicit shifts mathod
				if (abs(e[m]) <= EPS*dd) break;
			}
			if (m != l) {
				if (iter++ == 30) throw("Too many iterations in tqli");
				g=(d[l+1]-d[l])/(2.0*e[l]);		//form shift
				r=pythag(g,1.0);				//form demonimator in 11.4.22
				g=d[m]-d[l]+e[l]/(g+SIGN(r,g));		//d_m - k_s
				s=c=1.0;
				p=0.0;
				for (i=m-1;i>=l;i--) {			//plane rotation folowed by Givens rotation
					f=s*e[i];
					b=c*e[i];
					e[i+1]=(r=pythag(f,g));
					if (r == 0.0) {			//recover underflow
						d[i+1] -= p;
						e[m]=0.0;
						break;
					}
					s=f/r;					//define c and s in 11.4.22
					c=g/r;
					g=d[i+1]-p;
					r=(d[i]-g)*s+2.0*c*b;
					d[i+1]=g+(p=s*r);
					g=c*r-b;
					if (yesvecs) {
						for (k=0;k<n;k++) {			// form eigenvectors
							f=z[k][i+1];
							z[k][i+1]=s*z[k][i]+c*f;
							z[k][i]=c*z[k][i]-s*f;
						}
					}
				}
				if (r == 0.0 && i >= l) continue;
				d[l] -= p;
				e[l]=g;
				e[m]=0.0;
			}
		} while (m != l);
	}
}