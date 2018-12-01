#ifndef PROBLEM_HH
#define PROBLEM_HH    
#include <math.h> 



template <typename T> //takes a position x as input and returns cos(2x) for generic type T input x
T  bdy_term(T x) {
	return cos(2*x);
}

template <typename T> //takes a position x as input and returns 4cos(2x) for generic type T input x
T  source_term(T x) {
	return 4*cos(2*x);
}



#endif