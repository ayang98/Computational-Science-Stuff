#include "my_matrix.hh"
#include "proto_blas_lapack.hh"
#include <cstdio>
#include <iostream>

template <typename T>
my_matrix<T>::my_matrix(){ //default constructor sets number of rows and number of columns to 1
	rows = 1;
	columns = 1;
	pt  = new T*[columns]; //column major storing of elements for FORTRAN compatability
	pt[0]= new T[rows*columns]();
	for (int i = 1; i < columns ; i++){
		pt[i]= pt[0] + i*rows;
	}
}


template <typename T>
my_matrix<T>::my_matrix(int r, int c){ //user constructor allows user to set the number of rows and the number of columns
	if (r <= 0 || c <= 0){

		throw  "Rows or columns cannot be less than or equal zero in user constructor";

	}
	this->rows = r; //input number of rows
	this->columns = c; //input number of columns
	pt  = new T*[c]; //column major storing of elements 
	pt[0]= new T[r*c]();
	for (int i = 1; i < c ; i++){
		pt[i]= pt[0] + i*r;
	}
}

template<typename T>
my_matrix<T>::my_matrix(const my_matrix &old){ //copy constructor which creates a new my_matrix object as a copy of the input old my_matrix object

	//pre-allocate the memory for the copy
   	rows = old.rows; 
   	columns = old.columns; 
   	pt  = new T*[columns]; //column major order 
	pt[0]= new T[rows*columns]();
	for (int i = 1; i < columns ; i++){
		pt[i]= pt[0] + i*rows;
	}
	//assign each element of the copy to be the same as the input matrix 
	for (int j = 0; j < columns; j++){
   		for (int i = 0; i < rows; i++){
   			this->pt[j][i] = old.pt[j][i];
   		}
   	}
}

template<typename T>
my_matrix<T>::~my_matrix(){ //matrix destructor 
	delete [] pt[0];
	delete [] pt;
}


template<typename T>
T& my_matrix<T>::operator()(int row, int col){ //overide the () operator so that you can access elements of matrix A by calling A(i,j) 

	if (row < 0 || row >= this->rows){

		throw "Row index is out of bounds";
	}

	if (col < 0 || col >= this->columns){

		throw "Column index is out of bounds";
	}

	return this->pt[col][row];  	//returns a reference

}

template<typename T>
my_matrix<T>& my_matrix<T>::operator=(const my_matrix<T>& b){ //overload the equals operator so you can assign one matrix to another matrix of the
	//same dimensions by calling A = B

	if (this->rows != b.rows || this->columns != b.columns){ //need to check that both dimensions of both matrices are identical

		throw "Dimensions of given matrix has different dimensions than current object for equals operator";

	}

   	for (int j = 0; j < columns; j++){
   		for (int i = 0; i < rows; i++){

   			this->pt[j][i] = b.pt[j][i]; //assign each element of the current matrix to that of the input matrix
   		}
   	}

   	return *this;
 }


template<typename T>
my_matrix<T> my_matrix<T>::operator+(const my_matrix<T>& b) { //overload the addition operator so that you can add two matrices as A+B
   	
	if (this->rows != b.rows || this->columns != b.columns){ //need to check that both dimensions of both matrices are identical in order to add them

		throw "Dimensions of matrices being summed are not the same for addition operator";
	}

	my_matrix<T> matrix(this->rows, this->columns);
	for (int j = 0; j < columns; j++){
    	for (int i = 0; i < rows; i++){
    		matrix.pt[j][i] = this->pt[j][i] + b.pt[j][i]; //add the elements
    	}
    }

    return matrix;
}


template <> 
my_matrix<float> my_matrix<float>::operator*(const my_matrix<float>& b) //overload the matrix multiplication operator using sgemm_ for float matrices
//so that you can multiply two matrices as A*B
{ 

	if (this->columns != b.rows){  //the number of columns of matrix A must be the same as the number of rows of matrix B

		throw "Number of columns of A does not equal number of rows of B in multiplication operator";
	}

	int M = this->rows;
	int N = b.columns;
	int K = this->columns;
	float ALPHA = 1;
	int LDA = this->rows;
	int LDB = b.rows;
	float BETA = 0;
	my_matrix<float> C(M, N);
	int LDC = this->rows;


	sgemm_((char *) "N", (char *) "N", &M, &N, &K, &ALPHA, this->pt[0], &LDA, b.pt[0], &LDB, &BETA, C.pt[0], &LDC);

	return C;

}


template <> 
my_matrix<double> my_matrix<double>::operator*(const my_matrix<double>& b) //overload the matrix multiplication operator using dgemm_ for double matrices
//so that you can multiply two matrices as A*B

{ 
	if (this-> columns != b.rows){

		throw "Number of columns of A does not equal number of rows of B in multiplication operator";
	}

	int M = this->rows;
	int N = b.columns;
	int K = this->columns;
	double ALPHA = 1;
	int LDA = this->rows;
	int LDB = b.rows;
	double BETA = 0;
	my_matrix<double> C(M, N);
	int LDC = this->rows;

	dgemm_((char *) "N", (char *) "N", &M, &N, &K, &ALPHA, this->pt[0], &LDA, b.pt[0], &LDB, &BETA, C.pt[0], &LDC);

	return C;

} 



template <> 
my_matrix<float> my_matrix<float>::operator|(const my_matrix<float>& b) //overload the division operator for float matrices so that you can divide matrices
//as A|B
{ 
	//make copy of A and B, pass in those copies, return copy B 

	int N = this->rows;
	int NHRS = b.columns;
	my_matrix<float> A(*this); //this is a pointer, need to de-reference it 
	int LDA = this->rows;
	int IPIV[N];
	my_matrix<float> B(b);
	int LDB = b.rows;
	int INFO;

	sgesv_(&N, &NHRS, A.pt[0], &LDA, IPIV, B.pt[0], &LDB, &INFO);


	if (INFO !=0 ){ //only successful if INFO == 0

		throw "A is not invertible in division operator";
	}

	return B;

} 


template <> 
my_matrix<double> my_matrix<double>::operator|(const my_matrix<double>& b) //overload the division operator for double matrices so that you can divide matrices
//as A|B
{ 

	int N = this->rows;
	int NHRS = b.columns;
	my_matrix<double> A(*this); //this is a pointer, need to de-reference it 
	int LDA = this->rows;
	int IPIV [N];
	my_matrix<double> B(b);
	int LDB = b.rows;
	int INFO;


	dgesv_(&N, &NHRS, A.pt[0], &LDA, IPIV, B.pt[0], &LDB, &INFO);

	
	if (INFO !=0 ){ //only successful if INFO == 0

		throw "A is not invertible in division operator";
	}
	
	return B;
    
} 



//template instantiation 
template class my_matrix<float>; 
template class my_matrix<double>;

