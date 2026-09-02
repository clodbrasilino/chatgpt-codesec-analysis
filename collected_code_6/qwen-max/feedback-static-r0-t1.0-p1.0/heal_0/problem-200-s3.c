#include <stdio.h>
#include <stdlib.h>

void findMaxIndices(int *array, int size, int **result, int *resultSize) {
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    *result = (int *)malloc(size * sizeof(int));
    *resultSize = 0;
    for (int i = 0; i < size; i++) {
        if (array[i] == max) {
            (*result)[*resultSize] = i;
            (*resultSize)++;
        }
    }
}

int main() {
    int array[] = {4, 8, 6, 8, 3, 8, 5};
    int size = sizeof(array) / sizeof(array[0]);

    int *result = NULL;
    int resultSize = 0;

    findMaxIndices(array, size, &result, &resultSize);

    printf("Indices of the maximum value: ");
    for (int i = 0; i < resultSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}