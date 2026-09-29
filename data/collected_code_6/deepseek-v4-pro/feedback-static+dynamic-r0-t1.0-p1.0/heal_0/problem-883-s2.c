#include <stdio.h>
#include <stdlib.h>

void find_divisible(int *arr, int size, int m, int n, int **result, int *result_size) {
    *result = (int *)malloc(size * sizeof(int));
    if (*result == NULL) {
        *result_size = 0;
        return;
    }
    
    *result_size = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % m == 0 && arr[i] % n == 0) {
            (*result)[(*result_size)++] = arr[i];
        }
    }
    
    if (*result_size == 0) {
        free(*result);
        *result = NULL;
    } else {
        *result = (int *)realloc(*result, (*result_size) * sizeof(int));
        if (*result == NULL) {
            *result_size = 0;
        }
    }
}

int main() {
    int arr[] = {10, 15, 20, 30, 45, 60, 75, 90, 120};
    int size = sizeof(arr) / sizeof(arr[0]);
    int m = 3;
    int n = 5;
    int *result = NULL;
    int result_size = 0;
    
    find_divisible(arr, size, m, n, &result, &result_size);
    
    if (result != NULL && result_size > 0) {
        for (int i = 0; i < result_size; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }
    
    return 0;
}