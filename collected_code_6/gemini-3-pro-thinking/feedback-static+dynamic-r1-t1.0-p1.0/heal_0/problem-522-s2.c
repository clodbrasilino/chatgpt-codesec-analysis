#include <stdio.h>
#include <stdlib.h>

int find_longest_bitonic_subsequence(const int *arr, size_t n, size_t *result) {
    if (arr == NULL || result == NULL) {
        return -1;
    }

    if (n == 0) {
        *result = 0;
        return 0;
    }

    size_t *inc = (size_t *)malloc(n * sizeof(size_t));
    if (inc == NULL) {
        return -1;
    }

    size_t *dec = (size_t *)malloc(n * sizeof(size_t));
    if (dec == NULL) {
        free(inc);
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        inc[i] = 1;
        for (size_t j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + 1) {
                inc[i] = inc[j] + 1;
            }
        }
    }

    for (size_t i = n; i > 0; i--) {
        size_t idx = i - 1;
        dec[idx] = 1;
        for (size_t j = n - 1; j > idx; j--) {
            if (arr[idx] > arr[j] && dec[idx] < dec[j] + 1) {
                dec[idx] = dec[j] + 1;
            }
        }
    }

    size_t max_len = 0;
    for (size_t i = 0; i < n; i++) {
        if (inc[i] + dec[i] - 1 > max_len) {
            max_len = inc[i] + dec[i] - 1;
        }
    }

    *result = max_len;

    free(inc);
    free(dec);

    return 0;
}

int main(void) {
    int arr[] = { 1, 11, 2, 10, 4, 5, 2, 1 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    size_t lbs_length = 0;

    int status = find_longest_bitonic_subsequence(arr, n, &lbs_length);
    
    if (status != 0) {
        fprintf(stderr, "Error calculating longest bitonic subsequence.\n");
        return EXIT_FAILURE;
    }

    printf("%zu\n", lbs_length);

    return EXIT_SUCCESS;
}