#include <stdio.h>
#include <stdlib.h>
#include "numpy.h"

matrix_t* product(matrix_t mat1, matrix_t mat2)
{
    matrix_t *prod = malloc(sizeof(matrix_t));
    prod->rows = mat1.rows;
    prod->cols = mat2.cols;
    if (mat1.cols != mat2.rows)
        return prod;
    prod->matrix = calloc(mat1.rows, sizeof(float *));
    for (int i = 0; i < mat1.rows; i++)
    {
        prod->matrix[i] = malloc(sizeof(float));
    }
    for (int k = 0; k < mat2.cols; k++)
    {
        for (int i = 0; i < mat1.rows; i++)
        {
            for (int j = 0; j < mat1.cols; j++)
            {
                prod->matrix[i][k] += mat1.matrix[i][j] * mat2.matrix[j][k];
            }
        }
    }
    return prod;
}

array_t* new_array(int size) {
  array_t *newArr = malloc(sizeof(array_t));
  newArr->size = size;
  newArr->arr = calloc(newArr->size, sizeof(float));
  return newArr;
}

matrix_t *new_matrix(size_t rows, size_t cols, float grid[rows][cols]) {
    matrix_t *matrix = malloc(sizeof(matrix_t));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = calloc(rows, sizeof(float *));
    for (int i = 0; i < rows; i++) {
        matrix->matrix[i] = malloc(sizeof(float));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix->matrix[i][j] = grid[i][j];
        }
    }
    return matrix;
}

array_t* gradientDescent(int iter, int m, float alpha, array_t theta, matrix_t data, float (*diff)()) {
  int d = theta.size;
  array_t *weights = malloc(sizeof(array_t));
  weights->size = d;
  weights->arr = (float *) malloc(d * sizeof(float));
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < d; j++) {
      for (int k = 0; k < m; k++) {
        theta.arr[j] -= alpha*diff(j, theta, data.matrix[k]);
        weights->arr[j] = theta.arr[j];
      }
    }
  }
  return weights;
}

array_t* stochasticGradientDescent(int iter, int batchSize, int m, float alpha, array_t theta, matrix_t data, float (*diff)()) {
  int d = theta.size;
  array_t *weights = malloc(sizeof(array_t));
  weights->size = d;
  weights->arr = (float *) malloc(d * sizeof(float));
  for (int i = 0; i < iter; i++) {
    for (int k = 0; k < m; k += batchSize) {
      for (int b = k; b < k + batchSize; b++) {
        for (int j = 0; j < d; j++) {
          theta.arr[j] -= alpha*diff(j, theta, data.matrix[b]);
          weights->arr[j] = theta.arr[j];
        }
      }
    }
  }
  return weights;
}

array_t* slice(array_t array, int start, int stop, int step) {
  int size = (stop - start)/step;
  array_t *slicedArray = new_array(size);
  int k = 0;
  for (int i = start; i < stop; i += step) {
    slicedArray->arr[k] = array.arr[i];
    k += 1;
  }
  return slicedArray;
}

int* shape(matrix_t matrix) {
  int *ptr = malloc(sizeof(int));
  ptr[0] = matrix.rows;
  ptr[1] = matrix.cols;
  return ptr;
}

void print_arr(array_t *ptr) {
  for (int i = 0; i < ptr->size; i++) {
    printf("%f ", (ptr->arr)[i]);
  }
  printf("\n");
}

void print_matrix(matrix_t matrix) {
    for (int i = 0; i < matrix.rows; i++) {
        for (int j = 0; j < matrix.cols; j++) {
            printf("%f ", matrix.matrix[i][j]);
        }
        printf("\n");
    }
}