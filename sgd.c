#include <stdio.h>

float h(float theta[3], float x[4]) {
  float sum = 0.0;
  for (int i = 0; i < 3; i++) {
    sum += theta[i]*x[i];
  }
  return sum;
}

float cost(float theta[3], float data[5][4]) {
  float error = 0;
  for (int i = 0; i < 5; i++) {
    float sum = h(theta, data[i]);
    error += (sum - data[i][3]) * (sum - data[i][3]);
  }
  return error;
}

float diff(int d, int j, float theta[d], float xi[d + 1]) {
  return (h(theta, xi) - xi[d])*xi[j];
}

float* stochasticGradientDescent(int iter, int batchSize, int m, int d, float alpha, float theta[d], float data[m][d + 1], float (*diff)()) {
  for (int i = 0; i < iter; i++) {
    for (int k = 0; k < m; k += batchSize) {
      for (int b = k; b < k + batchSize; b += 1) {
        for (int j = 0; j < d; j++) {
            theta[j] -= alpha*diff(d, j, theta, data[b]);
        }
      }
    }
  }
  return theta;
}

void printArr(float arr[]) {
  printf("\nPrinting Array: ");
  int size = sizeof(&arr) / sizeof(&arr[0]);
  printf("%d", size);
  for (int i = 0; i < size; i++) {
    printf("%f ", arr[i]);
  }
  printf("\n");
}

int main()
{
  float theta[3] = {0, 0, 0};
  float alpha = 1e-5;
  float data[5][4] = {
    {1, 2, 3, 6},
    {1, 4, 6, 11},
    {1, 9, 10, 20},
    {1, 3, 5, 9},
    {1, 7, 7, 15}
  };
  float *weights = stochasticGradientDescent(10000, 1, 5, 3, alpha, theta, data, diff);
  printArr(weights);
  float res = cost(weights, data);
  printf("%f\n", res);
  float test[4]  = {1, 5, 8, 14};
  float ans = h(weights, test);
  printf("%f", ans);
  return 0;
}