#include <stdio.h>
#include <stdlib.h>
#include "numpy.h"

float h(array_t theta, float x[4]) {
  float sum = 0;
  for (int i = 0; i < theta.size; i++) {
    sum += theta.arr[i]*x[i];
  }
  return sum;
}

float cost(array_t theta, matrix_t data) {
  float error = 0;
  for (int i = 0; i < data.rows; i++) {
    float sum = h(theta, data.matrix[i]);
    error += (sum - data.matrix[i][data.cols - 1]) * (sum - data.matrix[i][data.cols - 1]);
  }
  return error;
}

float diff(int j, array_t theta, float xi[theta.size + 1]) {
  return (h(theta, xi) - xi[theta.size])*xi[j];
}

int main()
{
  array_t theta;
  theta.size = 3;
  theta.arr = (float *) calloc(theta.size, sizeof(float));
  float alpha = 5e-5;
  float dataPointer[5][4] = {
    {1, 2, 3, 6},
    {1, 4, 6, 11},
    {1, 9, 10, 20},
    {1, 3, 5, 9},
    {1, 7, 7, 15}
  };
  matrix_t *data = new_matrix(5, 4, dataPointer);
  array_t *weights = stochastic_gradient_descent(10000, 1, 5, alpha, theta, *data, diff);
  print_arr(weights);
  float res = cost(*weights, *data);
  printf("%f\n", res);
  float test[4]  = {1, 5, 8, 14};
  float ans = h(*weights, test);
  printf("%f", ans);
  return 0;
}