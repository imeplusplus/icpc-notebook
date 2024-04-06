// Gauss-Jordan Elimination with Scaled Partial Pivoting
// Extended to Calculate Inverses - O(n^3)
// To get more precision choose m[j][i] as pivot the element such that m[j][i] / mx[j] is maximized.
// mx[j] is the element with biggest absolute value of row j.

ld C[N][M]; // N = 1000, M = 2*N+1;
int row, col;

bool elim() {
	for(int i=0; i<row; ++i) {
		int p = i; // Choose the biggest pivot
		for(int j=i; j<row; ++j) if (abs(C[j][i]) > abs(C[p][i])) p = j;
		for(int j=i; j<col; ++j) swap(C[i][j], C[p][j]);

		if (!C[i][i]) return 0;

		ld c = 1/C[i][i]; // Normalize pivot line
		for(int j=0; j<col; ++j) C[i][j] *= c;

		for(int k=i+1; k<col; ++k) {
			ld c = -C[k][i]; // Remove pivot variable from other lines
			for(int j=0; j<col; ++j) C[k][j] += c*C[i][j];
		}
	}

	// Make triangular system a diagonal one
	for(int i=row-1; i>=0; --i) for(int j=i-1; j>=0; --j) {
		ld c = -C[j][i];
		for(int k=i; k<col; ++k) C[j][k] += c*C[i][k];
	}

	return 1;
}

// Finds inv, the inverse of matrix m of size n x n.
// Returns true if procedure was successful.
bool inverse(int n, ld m[N][N], ld inv[N][N]) {
	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j)
		C[i][j] = m[i][j], C[i][j+n] = (i == j);

	row = n, col = 2*n;
	bool ok = elim();

	for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) inv[i][j] = C[i][j+n];
	return ok;
}

// Solves linear system m*x = y, of size n x n
bool linear_system(int n, ld m[N][N], ld *x, ld *y) {
	for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j) C[i][j] = m[i][j];
	for(int j = 0; j < n; ++j) C[j][n] = x[j];

	row = n, col = n+1;
	bool ok = elim();

	for(int j=0; j<n; ++j) y[j] = C[j][n];
	return ok;
}

