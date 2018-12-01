#ifndef SOLVER_POISSON_HH
#define SOLVER_POISSON_HH    
#include "problem.hh"
#include<iostream>
#include "my_matrix.hh"


//The following function implements the finite-difference method to solve the Poisson Equation 
//N = the number of points of discretization
//a = the first boundary point
//b = the last boundary point
template <typename T>
my_matrix<T> solver_poisson(int N, T a, T b) {

	my_matrix<T> F(N,1); //create the F vector as Nx1

	F(0,0) = bdy_term(a);

	F(N-1,0) = bdy_term(b);

	T h = (b-a)/(N-1); //h is the step size

	if (N>2){
		for (int i = 1; i < N-1; i++){
			F(i,0) = source_term(a+h*i);
		}
	}

	/*
	for (int i = 0; i<N; i++){
		std::cout << F(i,0) << std::endl;
	}
	*/
		

	my_matrix<T> A(N,N); //create the A matrix as NxN

	A(0,0) = 1;
	A(0,1) = 0;
	A(N-1,N-2) = 0;
	A(N-1,N-1) = 1;
	for (int i = 1; i< N - 1; i++){
		for (int j = 0; j < N; j++){
			if (i == j){
				A(i,j) = 2/(h*h);
			}
			else if (j-i == 1){
				A(i,j) = -1/(h*h);
			}
			else if (j-i == -1){
				A(i,j) = -1/(h*h);
			}
			else{
				A(i,j) = 0;
			}
			
		}
	}

	/*
	for (int i = 0; i< N; i++){
		for (int j = 0; j<N; j++){
			std::cout << A(i,j) << "\t";
		}
		std::cout << std::endl;
	}
	*/




	my_matrix<T> U = A|F; //the solution is A|F
	
	
	return U;

	
}




#endif