#ifndef MATRIX_2D_H
#define MATRIX_2D_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
	int rows;
	int columns;
	double **pt;
	char *tag;
	int status;

} Matrix;

Matrix matrix_constuctor(int n1, int n2, char *tag);

void destructor();

void matrix_set(Matrix *m, int row, int column, double value);

double matrix_get(Matrix m, int row, int column);

Matrix matrix_add(Matrix m1, Matrix m2, char *tag);

Matrix matrix_products(Matrix m1, Matrix m2, char *tag);

Matrix matrix_read(char *filename, char *tag);

void matrix_write(Matrix m);


#endif