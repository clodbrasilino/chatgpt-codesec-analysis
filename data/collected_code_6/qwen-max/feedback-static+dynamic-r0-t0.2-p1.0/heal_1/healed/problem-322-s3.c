#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void find_min_indices(const int *arr, int n, int **result, int *result_size) {
    if (n <= 0) return;
    int min = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    *result_size = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == min) {
            (*result)[(*result_size)++] = i;
        }
    }
}

int main() {
    int arr[] = {3, 1, 2, 1, 5, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *result = (int *)malloc(n * sizeof(int));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    int result_size = 0;

    find_min_indices(arr, n, &result, &result_size);

    for (int i = 0; i < result_size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}