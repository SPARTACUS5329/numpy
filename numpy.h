#pragma once
#include <stdio.h>

typedef struct Array {
  int size;
  float *arr;
} Array;

void printArr(struct Array *ptr);