#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void find_min_indices(int *arr, int n, int **result, int *result_size) {
    if (n <= 0 || arr == NULL) {
        *result = NULL;
        *result_size = 0;
        return;
    }

    int min_value = INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (arr[i] < min_value) {
            min_value = arr[i];
        }
    }

    *result_size = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == min_value) {
            (*result_size)++;
        }
    }

    *result = (int *)malloc((*result_size) * sizeof(int));
    if (*result == NULL) {
        *result_size = 0;
        return;
    }

    int index = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] == min_value) {
            (*result)[index++] = i;
        }
    }
}

int main() {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
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