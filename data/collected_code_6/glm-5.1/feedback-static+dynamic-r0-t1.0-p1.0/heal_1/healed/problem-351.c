#include <stdio.h>
#include <stdlib.h>

int find_first_k_occurrence(const int *arr, size_t n, int k) {
    if (arr == NULL || n == 0 || k <= 0) {
        return -1;
    }

    int min_val = arr[0];
    int max_val = arr[0];

    for (size_t i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    size_t range = (size_t)(max_val - min_val + 1);
    size_t *counts = (size_t *)calloc(range, sizeof(size_t));
    if (counts == NULL) {
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        counts[arr[i] - min_val]++;
    }

    int result = -1;
    for (size_t i = 0; i < n; i++) {
        if (counts[arr[i] - min_val] == k) {
            result = arr[i];
            break;
        }
    }

    free(counts);
    return result;
}

int main(void) {
    int arr[] = {1, 2, 3, 2, 4, 1, 5, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 2;

    int res = find_first_k_occurrence(arr, n, k);
    printf("%d\n", res);

    return 0;
}