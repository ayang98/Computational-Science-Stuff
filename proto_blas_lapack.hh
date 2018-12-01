#ifndef PROTO_BLAS_LAPACK_HH
#define PROTO_BLAS_LAPACK_HH

extern "C" {
	void sgesv_(
		int* N, 
		int* NRHS, 
		float* A, 
		int* LDA, 
		int* IPIV, 
		float* B, 
		int* LBD, 
		int* INFO);  


	void dgesv_(
		int* N, 
		int* NRHS, 
		double* A, 
		int* LDA, 
		int* IPIV, 
		double* B, 
		int* LBD, 
		int* INFO);


	void sgemm_(
		char*, 
		char*, 
		int*, 
		int*, 
		int*, 
		float*, 
		float*, 
		int*, 
		float*, 
		int*, 
		float*, 
		float*, 
		int*);

	void dgemm_(
		char* TRANSA, 
		char* TRANSB, 
		int* M, 
		int* N, 
		int* K, 
		double* ALPHA, 
		double* A, 
		int* LDA, 
		double* B, 
		int* LDB, 
		double* BETA, 
		double* C, 
		int* LDC);

};

#endif