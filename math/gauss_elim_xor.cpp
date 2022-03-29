// Gauss Elimination for xor boolean operations
// Return false if not possible to solve
// Use boolean matrixes 0-indexed
// n equations, m variables, O(n * m * m)
// eq[i][j] = coefficient of j-th element in i-th equation
// r[i] = result of i-th equation
// Return ans[j] = xj that gives the lexicographically greatest solution (if possible)
// (Can be changed to lexicographically least, follow the comments in the code)
// WARNING!! The arrays get changed during de algorithm

bool eq[N][M], r[N], ans[M];

bool gauss_xor(int n, int m){
	for(int i = 0; i < m; i++)
		ans[i] = true;
	int lid[N] = {0}; // id + 1 of last element present in i-th line of final matrix
	int l = 0;
	for(int i = m - 1; i >= 0; i--){
		for(int j = l; j < n; j++)
			if(eq[j][i]){ // pivot
				swap(eq[l], eq[j]);
				swap(r[l], r[j]);
			}
		if(l == n || !eq[l][i])
			continue;
		lid[l] = i + 1;
		for(int j = l + 1; j < n; j++){ // eliminate column
			if(!eq[j][i])
				continue;
			for(int k = 0; k <= i; k++)
				eq[j][k] ^= eq[l][k];
			r[j] ^= r[l];
		}
		l++;
	}
	for(int i = n - 1; i >= 0; i--){ // solve triangular matrix
		for(int j = 0; j < lid[i + 1]; j++)
			r[i] ^= (eq[i][j] && ans[j]);
		// for lexicographically least just delete the for bellow
		for(int j = lid[i + 1]; j + 1 < lid[i]; j++){
			ans[j] = true;
			r[i] ^= eq[i][j];
		}
		if(lid[i])
			ans[lid[i] - 1] = r[i];
		else if(r[i])
			return false;
	}
	return true;
}
