#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void find_min_indices(const int *arr, int n, int **result, int *result_size) {
    *result = NULL;
    *result_size = 0;
    if (n <= 0) return;

    int min_value = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    *result = (int *)malloc(n * sizeof(int));
    if (*result == NULL) {
        *result_size = 0;
        return;
    }

    for (int i = 0; i < n; ++i) {
        if (arr[i] == min_value) {
            (*result)[(*result_size)++] = i;
        }
    }
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int *result = NULL;
    int result_size = 0;

    find_min_indices(arr, n, &result, &result_size);

    for (int i = 0; i < result_size; ++i) {
        printf("%d ", result[i]);
    }
    printf("\n");

    free(result);
    return 0;
}