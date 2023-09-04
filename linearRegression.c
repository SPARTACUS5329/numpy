#include <stdio.h>
#include <stdlib.h>
#include "numpy.h"

float h(struct Array theta, float x[4]) {
  float sum = 0;
  for (int i = 0; i < theta.size; i++) {
    sum += theta.arr[i]*x[i];
  }
  return sum;
}

float cost(struct Array theta, float data[5][4]) {
  float error = 0;
  for (int i = 0; i < 5; i++) {
    float sum = h(theta, data[i]);
    error += (sum - data[i][3]) * (sum - data[i][3]);
  }
  return error;
}

float diff(int d, int j, struct Array theta, float xi[d + 1]) {
  return (h(theta, xi) - xi[d])*xi[j];
}

struct Array* gradientDescent(int iter, int m, int d, float alpha, struct Array theta, float data[m][d + 1], float (*diff)()) {
  struct Array *weights = malloc(sizeof(struct Array));
  weights->size = d;
  weights->arr = (float *) malloc(d * sizeof(float));
  for (int i = 0; i < iter; i++) {
    for (int j = 0; j < d; j++) {
      for (int k = 0; k < m; k++) {
        theta.arr[j] -= alpha*diff(d, j, theta, data[k]);
        weights->arr[j] = theta.arr[j];
      }
    }
  }
  return weights;
}

int main()
{
  struct Array theta;
  theta.size = 3;
  theta.arr = (float *) calloc(theta.size, sizeof(float));
  float alpha = 5e-5;
  float data[5][4] = {
    {1, 2, 3, 6},
    {1, 4, 6, 11},
    {1, 9, 10, 20},
    {1, 3, 5, 9},
    {1, 7, 7, 15}
  };
  struct Array *weights = gradientDescent(10000, 5, 3, alpha, theta, data, diff);
  printf("size of weights: %d\n", weights->size);
  printArr(weights);
  float res = cost(*weights, data);
  printf("%f\n", res);
  float test[4]  = {1, 5, 8, 14};
  float ans = h(*weights, test);
  printf("%f", ans);
  return 0;
}