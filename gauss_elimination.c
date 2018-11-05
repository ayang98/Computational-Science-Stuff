#include "gauss_elimination.h"

Matrix matrix_gauss_inverse(Matrix *m, char *name){

	if (m->pt == NULL){   //check if the pointer is null
		printf("Null pointer error\n");
	}

	int rows = m->rows;
	int columns = m->columns;
	Matrix zero_matrix = matrix_constructor(rows, rows, name); //create the zero matrix where every element is zero
	for (int i = 0; i<rows; i++){
		for (int j = 0; j<rows; j++){
			matrix_set(&zero_matrix, i, j, 0);
		}
	}
	Matrix null_matrix = matrix_constructor(0,0,name);

	if (m->status==0){ //matrix is not correct
		printf("The status is 0\n");
		return null_matrix;
	}

	else if (rows != columns){ //matrix is not square 
		printf("The matrix is not square\n");
		return null_matrix;
	}

	Matrix augmented_matrix = matrix_constructor(rows, 2*rows, name);
	//make first n columns same as original matrix m
	for (int i = 0; i < rows; i++){
		for(int j = 0; j < columns; j++){

			matrix_set(&augmented_matrix, i, j, m->pt[i][j]);

		}
	}
	for (int i = 0; i < rows; i++){
		for (int j= rows; j < 2*rows; j++){

			if (j-i == rows){
				matrix_set(&augmented_matrix, i,j,1);
			}
			else{
				matrix_set(&augmented_matrix, i,j,0);
			}
			

		}
	}
	//return augmented_matrix;
	double r;
	int stop;
	double temp;
	for (int i = 0; i < columns; i++){

		if (augmented_matrix.pt[i][i] == 0){

			for (int j = i+1; j < rows; j++){

				if (augmented_matrix.pt[j][i] != 0){

					stop = j; //if you find a row with a non-zero element for the given column, then store it and break

					break;
				}
				else{
					stop = -1;
				}
			}
			if (stop == -1){
				printf("Non-invertible matrix\n");
				return zero_matrix; //the matrix is non-invertible if an entire column is zero
			}
			matrix_swap_row(&augmented_matrix, i, stop); //swap row with non-zero start with the zero start row
		}
	
	
	
		for (int j = 0; j< rows; j++){

			if (i!=j){

				temp = augmented_matrix.pt[j][i]/augmented_matrix.pt[i][i]; //for each row not equal to i, turn the first element into 0 by subtracting the
				//ith row times some factor temp

				matrix_subtract_row(&augmented_matrix, j, i, temp); //subtract row i times factor temp from row j

				}
			}
		}
	
	//return augmented_matrix;
	for (int i = 0; i< rows; i++){
		for (int j = 0; j< rows; j++){

			if (i == j){
				if (augmented_matrix.pt[i][j] != 1){
					matrix_divide_row(&augmented_matrix, i, augmented_matrix.pt[i][j]); //ensure each diagonal element is 1
				}
			}
			else{
				
				//printf("%f\n", augmented_matrix.pt[i][j]);
				if (abs(augmented_matrix.pt[i][j])>0){
					printf("Non-invertible matrix\n");
					return zero_matrix; //IMPORTANT- the matrix is not invertible if there are still non-zero entries in the non-diagonal elements of the
					//square matrix even after the algorithm has finished.
				}
			}
		}
	}
	//return augmented_matrix;
	Matrix final_matrix = matrix_constructor(rows, rows, name); //break apart the augmented matrix so only the inverse remains
		for (int i = 0; i<rows; i++){
			for (int j = rows; j<2*rows; j++){

				matrix_set(&final_matrix, i,j-rows,augmented_matrix.pt[i][j]);

			}
		}
	

	destructor(&augmented_matrix);

	return final_matrix;
}




void matrix_swap_row(Matrix *m, int n1, int n2){

	if (m->pt == NULL){   //check if the pointer is null
		printf("Null pointer error\n");
	}

	if (m->status==0){
		printf("%s\n",m->tag);
		printf("matrix_swap_row error 1\n");
	}
	else if(n1 < 0 || n1 > m->rows-1){
		printf("%s\n",m->tag);
		printf("matrix_swap_row error 2\n");
	}

	else if(n2 < 0 || n2 > m->rows-1){
		printf("%s\n",m->tag);
		printf("matrix_swap_row error 3\n");
	}

	int columns = m->columns;

	double temp;
	double new;
	for (int j = 0; j < columns; j++){

		temp = m -> pt[n1][j]; //set temp to first element

		new = m -> pt[n2][j]; //set new to second element

		m -> pt[n1][j] = new; //set first element to new (second element)

		m -> pt[n2][j] = temp; //set second element to temp (first element)

	}

}


void matrix_divide_row(Matrix *m, int n1, double r){
	if (m->pt == NULL){   //check if the pointer is null
		printf("Null pointer error\n");
	}

	if (m->status==0){
		printf("%s\n",m->tag);
		printf("matrix_divide_row error 1\n");
	}
	else if(n1 < 0 || n1 > m->rows-1){
		printf("%s\n",m->tag);
		printf("matrix_divide_row error 2\n");
	}

	int columns = m->columns;
	double new;
	for (int j = 0; j < columns; j++){

		new = m-> pt[n1][j];
		m->pt[n1][j] = new/(r); //divide each element in the row by r
	}
}



void matrix_subtract_row(Matrix *m, int n1, int n2, double r){
	if (m->pt == NULL){   //check if the pointer is null
		printf("Null pointer error\n");
	}

	if (m->status==0){
		printf("%s\n",m->tag);
		printf("matrix_subtract_row error 1\n");
	}
	else if(n1 < 0 || n1 > m->rows-1){
		printf("%s\n",m->tag);
		printf("matrix_subtract_row error 2\n");
	}

	else if(n2 < 0 || n2 > m->rows-1){
		printf("%s\n",m->tag);
		printf("matrix_subtract_row error 3\n");
	}

	int columns = m->columns;
	double new1;
	double new2;

	for (int j = 0; j < columns; j++){

		new1 = m-> pt[n1][j];
		new2 = m -> pt[n2][j];
		m->pt[n1][j] = new1- (new2)*r; //subtract r times the second row from the first row 
	}

}








