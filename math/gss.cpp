double gss(double l, double r) {
	double m1 = r-(r-l)/gr, m2 = l+(r-l)/gr;
	double f1 = f(m1), f2 = f(m2);
	while(fabs(l-r)>EPS) {
		if(f1>f2) l=m1, f1=f2, m1=m2, m2=l+(r-l)/gr, f2=f(m2);
		else r=m2, f2=f1, m2=m1, m1=r-(r-l)/gr, f1=f(m1);
	}
	return l;
}
