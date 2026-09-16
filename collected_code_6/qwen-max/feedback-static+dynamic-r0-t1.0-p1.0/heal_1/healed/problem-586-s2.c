#include <stdio.h>
#include <stdlib.h>

void splitAndAdd(const int *arr, int n, int k, int **result) {
    int temp[k];
    for (int i = 0; i < k; i++) {
        temp[i] = arr[i];
    }
    *result = (int*)malloc(n * sizeof(int));
    if (*result == NULL) {
        exit(1);
    }
    for (int i = 0; i < n - k; i++) {
        (*result)[i] = arr[i + k];
    }
    for (int i = 0; i < k; i++) {
        (*result)[n - k + i] = temp[i];
    }
}

int* createArray(int n) {
    int *arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

void printArray(const int *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int n = 10;
    int k = 3;
    int *arr = createArray(n);
    printArray(arr, n);
    int *newArr;
    splitAndAdd(arr, n, k, &newArr);
    printArray(newArr, n);
    free(arr);
    free(newArr);
    return 0;
}