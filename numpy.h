#pragma once

typedef struct Array {
  size_t size;
  float *arr;
} array_t;

typedef struct Matrix {
  size_t rows;
  size_t cols;
  float **matrix;
} matrix_t;

void print_arr(array_t*);
void print_matrix(matrix_t);
int* shape(matrix_t);
array_t* new_array(int);
matrix_t* new_matrix(size_t rows, size_t cols, float grid[rows][cols]);
array_t* copy(array_t);
array_t* view(array_t);
array_t* slice(array_t, int, int, int);
matrix_t* product(matrix_t, matrix_t);
array_t* gradient_descent(int, int, float, array_t, matrix_t, float (*)());
array_t* stochastic_gradient_descent(int, int, int, float, array_t, matrix_t, float (*)());