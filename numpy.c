#include <stdio.h>
#include <stdlib.h>

struct Array {
    int size;
    float *arr;
};

int **product(int rows1, int cols1, int rows2, int cols2, int arr1[rows1][cols1], int arr2[rows2][cols2])
{
    int **prod = (int **)(malloc(rows1 * sizeof(int *)));
    if (cols1 != rows2)
        return prod;
    for (int i = 0; i < rows1; i++)
    {
        prod[i] = (int *)(malloc(cols2 * sizeof(int)));
    }
    for (int k = 0; k < cols2; k++)
    {
        for (int i = 0; i < rows1; i++)
        {
            for (int j = 0; j < cols1; j++)
            {
                prod[i][k] += arr1[i][j] * arr2[j][k];
            }
        }
    }
    return prod;
}

// void printArr(struct Array *ptr) {
//   printf("size of ptr: %d\n", ptr->size);
//   for (int i = 0; i < ptr->size; i++) {
//     printf("%f ", ptr->arr[i]);
//   }
//   printf("\n");
// }

void printMatrix(int rows, int cols, int arr[rows][cols]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j > cols; j++) {
            printf("%d", arr[i][j]);
        }
    }
}