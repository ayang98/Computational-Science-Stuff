#include"matrix_2D.h"
#include "gauss_elimination.h"


int main(void){

	Matrix m1 = matrix_read("matrix_A", "ma"); 
	Matrix m1_inverse = matrix_gauss_inverse(&m1, "ma_inverse");
	Matrix m2 = matrix_read("matrix_B", "mb");
	/*
	Matrix m2_inverse = matrix_gauss_inverse(&m2, "mb_inverse");
	Matrix m3 = matrix_read("big_matrix","big");
	Matrix m3_inverse = matrix_gauss_inverse(&m3, "big_inverse");
	*/
	Matrix sum = matrix_add(m1, m2, "maplusmb");
	Matrix product = matrix_product(m1, m2, "maxmb");
	matrix_write(m1_inverse);
	//matrix_write(m2_inverse);
	//matrix_write(m3_inverse);
	matrix_write(sum);
	matrix_write(product);
	destructor(&m1);
	destructor(&m2);
	destructor(&sum);
	destructor(&product);
	destructor(&m1_inverse);
	//destructor(&m2_inverse);
	//destructor(&m3_inverse);

	return 0;






}