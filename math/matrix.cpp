/*
	This code assumes you are multiplying two matrices that can be multiplied: (A nxp * B pxm)
	Matrix fexp assumes square matrices
*/

const int MOD = 1e9 + 7;
typedef long long ll;
typedef long long type;

struct matrix{
	//matrix n x m
	vector<vector<type>> a;
	int n, m;
	matrix() = default;

	matrix(int _n, int _m) : n(_n), m(_m){
		a.resize(n, vector<type>(m));
	}

	matrix operator *(matrix other){
		matrix result(this->n, other.m);
		for(int i = 0; i < result.n; i++){
			for(int j = 0; j < result.m; j++){
				for(int k = 0; k < this->m; k++){
					result.a[i][j] = (result.a[i][j] + a[i][k] * other.a[k][j]);
					//result.a[i][j] = (result.a[i][j] + (a[i][k] * other.a[k][j]) % MOD) % MOD;
				}
			}
		}
		return result;
	}
};

matrix identity(int n){
	matrix id(n, n);
	for(int i = 0; i < n; i++) id.a[i][i] = 1;
	return id;
}

matrix fexp(matrix b, ll e){
	matrix ans = identity(b.n);
	while(e){
		if(e & 1) ans = (ans * b);
		b = b * b;
		e >>= 1;
	}
	return ans;
}