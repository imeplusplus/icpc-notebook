// O(N * 2^N)
// A[i] = initial values
// Calculate F[i] = Sum of A[j] for j subset of i
for(int i = 0; i < (1 << N); i++)
	F[i] = A[i];
for(int i = 0; i < N; i++)
    for(int j = 0; j < (1 << N); j++)
	    if(j & (1 << i))
		    F[j] += F[j ^ (1 << i)];
