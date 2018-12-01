#include <iostream> 
#include <cstdio>
#include "solver_poisson.hh"




typedef double P; //create a matrix of doubles
//typedef float P;

int main(int argc, char** argv){
	try {  //try and run the code
		int N = std::atoi(argv[1]);
		double a = std::atof(argv[2]);
		double b = std::atof(argv[3]);

		if (argc != 4){

			throw "Enter the number of elements N>1 and the boundaries a<b of the domain when running the program";

		} 

		if (N <= 1){

			throw "N has to be larger than 1";
		}

		if (a >= b){

			throw "a has to be smaller than b";

		}

		my_matrix<P> F1(2,3);
		my_matrix<P> F2(3,3);

		//print the matrix F1
		std::cout << "Matrix F1" << std::endl;

		for (int i = 0; i < 2; i++){
			for (int j = 0 ; j < 3; j++){
				F1(i,j) = 1;
				std::cout << F1(i, j) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		//print the matrix F2
		std::cout << "Matrix F2" << std::endl;

		for (int i = 0; i < 3; i++){
			for (int j = 0 ; j < 3; j++){
				F2(i,j) = 2;
				std::cout << F2(i, j) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		//print the matrix F3 = F1 + F1
		std::cout << "Matrix F3" << std::endl;

		my_matrix<P> F3 = F1+F1;

		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 3; ++j) {
				std::cout << F3(i, j) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		//print the matrix F4 = F1*F2
		std::cout << "Matrix F4" << std::endl;

		my_matrix<P> F4 = F1*F2;

		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 3; ++j) {
				std::cout << F4(i, j) << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;

		//std::cout<< bdy_term(0) << std::endl;
		//my_matrix<double> A = solver_poisson(N, a, b);
		my_matrix<double> approx_double = solver_poisson(N, a, b);

		double h = (b-a)/(N-1);


		FILE* output_file = std::fopen("my_solution", "w"); //create file object to write to


		//write x_i, u_i to file
		for (int i = 0; i < N; i++){

			fprintf(output_file, "%lf %lf\n", a+h*i, approx_double(i,0));
		}

		std::fclose(output_file); //close the file
		
		
	}
	catch (const char* e) { //catch any exception thrown 
		std::cout << e << std::endl;
		return 1;
	}

	return 0;
}