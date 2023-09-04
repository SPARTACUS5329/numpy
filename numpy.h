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
matrix_t* new_matrix(size_t rows, size_t cols, float grid[rows][cols]);
void print_matrix(matrix_t);
matrix_t* product(matrix_t, matrix_t);
array_t* gradientDescent(int, int, float, array_t, matrix_t, float (*)());
array_t* stochasticGradientDescent(int, int, int, float, array_t, matrix_t, float (*)());