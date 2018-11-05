#ifndef GAUSS_ELIMINATION_H
#define GAUSS_ELIMINATION_H
#include "matrix_2D.h"


Matrix matrix_gauss_inverse(Matrix *m, char *tag);

void matrix_swap_row(Matrix *m, int n1, int n2);

void matrix_divide_row(Matrix *m, int n1, double r);

void matrix_subtract_row(Matrix *m, int n1, int n2, double r);

#endif