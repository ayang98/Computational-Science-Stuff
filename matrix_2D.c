#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"matrix_2D.h"


char* strdup (const char * str_in){
	int n = strlen ( str_in ) + 1; // Input length + end string
	char * str_out = malloc (n * sizeof (char)); // Allocation
	if (str_out != NULL){ // Check if malloc was successfull
		strcpy (str_out , str_in);
	}
	return str_out;
}


Matrix matrix_constuctor(int n1, int n2, char *name){
	Matrix null_matrix;
	null_matrix.rows = 0;
	null_matrix.columns = 0;
	null_matrix.status = 0;
	null_matrix.pt = NULL;
	null_matrix.tag = strdup(name);

	if (n1 == 0 || n2 == 0){
		return null_matrix;
	}

	else if (n1 < 1 || n2 < 1){
		return null_matrix;
	}

	Matrix new_matrix;
	new_matrix.rows = n1;
	new_matrix.columns = n2;
	new_matrix.status = 1;
	new_matrix.tag = strdup(name);

 	new_matrix.pt = malloc (n1 * sizeof(double*));
 	 if (new_matrix.pt == NULL){
 		return null_matrix;
 	}
 	int i;
	for (i = 0; i < n1 ; i++){
		new_matrix.pt[i] = malloc(n2 *sizeof(double)); //create pointer for each row (row has n2 elements)
		if (new_matrix.pt[i] == NULL){
 			return null_matrix;
 		}
	}

	return new_matrix;
	
}

void destructor(Matrix *m){

	m->rows = 0;
	m->columns= 0;
	m->status = 0;

	for (int i =0; i < m->rows ; i ++){
		free(m->pt[i]); //free everything in row pointed to by pt[i]
		m -> pt[i] = NULL; 
 	
	}

	free(m->pt); //free all rows pointed to by pt
	m -> pt = NULL;
	free (m->tag);
	m->tag = NULL;
}


void matrix_set(Matrix* m, int row, int column, double value){

	if (m->status==0){
		printf("%s\n",m->tag);
		printf("matrix_set error 1\n");
	}
	else if(row < 0 || row > m->rows){
		printf("%s\n",m->tag);
		printf("matrix_set error 2\n");
	}
	else if(column < 0 || column > m->columns){
		printf("%s\n", m->tag);
		printf("matrix_set error 3\n");
	}

	else{
		m->pt[row][column] = value;
	}

}


double matrix_get(Matrix m, int row, int column){
	if (m.status==0){
		printf("%s\n",m.tag);
		printf("matrix_get error\n");
	}
	else if(row < 0 || row > m.rows){
		printf("%s\n",m.tag);
		printf("matrix_get error 2\n");
	}
	else if(column < 0 || column > m.columns){
		printf("%s\n", m.tag);
		printf("matrix_get error 3\n");
	}

	else {
		return m.pt[row][column];
	}

}



Matrix matrix_add(Matrix m1, Matrix m2, char *name){

	Matrix output;
	output.rows = m1.rows;
	output.columns = m1.columns;
	output.status = 1;
	output.tag = strdup(name);
	if (m1.status == 0){
		printf("%s\n",m1.tag);
		printf("matrix_add error\n");
	}
	else if (m2.status == 0){
		printf("%s\n",m2.tag);
		printf("matrix_add error\n");
	}

	else if(m1.rows != m2.rows || m1.columns != m2.columns){
		printf("matrix_add error\n");
		Matrix null_matrix = matrix_constuctor(0,0,name);
		return null_matrix;
	}
	else{

		Matrix output = matrix_constuctor(m1.rows, m1.columns, name);
		output.status = 1;
		for (int i = 0; i < m1.rows; i++){
			for (int j = 0; j <  m1.columns; j++){
				matrix_set(&output, i, j, matrix_get(m1, i, j) + matrix_get(m2, i, j));

			}
		}

		return output;
	}

}



Matrix matrix_product(Matrix m1, Matrix m2, char *name){
	if (m1.status == 0){
		printf("%s\n",m1.tag);
		printf("matrix_product error\n");
	}

	else if (m2.status == 0){
		printf("%s\n",m1.tag);
		printf("matrix_product error\n");
	}

	else if(m1.columns != m2.rows){

		printf("matrix_product error\n");
		Matrix null_matrix = matrix_constuctor(0,0,name);
		return null_matrix;
	}
	else{
		Matrix output = matrix_constuctor(m1.rows, m2.columns, name);
		for (int i=0; i< m1.rows; i++){
			for (int j=0; j<m2.columns; j++){
				for (int k = 0; k < m1.columns; k++){

					matrix_set(&output, i , j, matrix_get(m1,i,k) * matrix_get(m2, k,j));
				}
			}
		}

	return output;

	}

}


Matrix matrix_read(char *filename, char *name){

	
	FILE *fp;

	fp = fopen(filename, "r");

	int rows;
 	int columns;
 	fscanf(fp, "%d", &rows);
 	fscanf(fp, "%d", &columns);

 	Matrix read_matrix = matrix_constuctor(rows, columns, name);

 	double entry;
 	int i, j;
 	for (i = 0; i < rows; ++i) {
 		for (j = 0; j < columns; ++j) {
 			fscanf(fp, "%lf", &entry);
 			//printf("%lf ", entry);
 			matrix_set(&read_matrix, i, j, entry);
 		}
 	}

    fclose(fp);

    return read_matrix;


}



void matrix_write(Matrix m){

	FILE *fp;
	fp = fopen(m.tag, "w+");
	fprintf(fp, "%d ", m.rows);
 	fprintf(fp, "%d\n", m.columns);

 	for (int i = 0; i < m.rows; i++) {
 		for (int j = 0; j < m.columns; j++) {

 			fprintf(fp, "%lf ", matrix_get(m, i, j));
 			//printf("%lf ", entry);
 		}

 		fprintf(fp, "\n");

 	}

   	fclose(fp);

}
