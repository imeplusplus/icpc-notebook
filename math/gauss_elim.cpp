//Gaussian Elimination
//double A[N][M+1], X[M]

// if n < m, there's no solution
// column m holds the right side of the equation
// X holds the solutions

for(int j=0; j<m; j++) { //collumn to eliminate
	int l = j;
	for(int i=j+1; i<n; i++) //find largest pivot
		if(abs(A[i][j])>abs(A[l][j]))
			l=i;
	if(abs(A[i][j]) < EPS) continue;
	for(int k = 0; k < m+1; k++) { //Swap lines
		swap(A[l][k],A[j][k]);
	}
	for(int i = j+1; i < n; i++) { //eliminate column
		double t=A[i][j]/A[j][j];
		for(int k = j; k < m+1; k++)
			A[i][k]-=t*A[j][k];
	}
}

for(int i = m-1; i >= 0; i--) { //solve triangular system
	for(int j = m-1; j > i; j--)
		A[i][m] -= A[i][j]*X[j];
	X[i]=A[i][m]/A[i][i];
}

