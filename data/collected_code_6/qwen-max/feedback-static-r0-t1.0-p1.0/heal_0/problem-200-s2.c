#include <stdio.h>
#include <stdlib.h>

void find_max_indices(int *arr, int n, int **result, int *result_size) {
    if (n == 0) return;
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val)
            max_val = arr[i];
    }
    *result = (int *)malloc(n * sizeof(int));
    *result_size = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == max_val) {
            (*result)[*result_size] = i;
            (*result_size)++;
        }
    }
}

int main() {
    int arr[] = {3, 5, 7, 4, 9, 7, 2, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *result = NULL;
    int result_size = 0;
    
    find_max_indices(arr, n, &result, &result_size);

    for (int i = 0; i < result_size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}