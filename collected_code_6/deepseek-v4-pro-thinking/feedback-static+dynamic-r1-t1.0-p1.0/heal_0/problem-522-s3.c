#include <stdio.h>
#include <stdlib.h>

int longestBitonicSubsequence(const int arr[], int n) {
    if (n <= 0) {
        return 0;
    }

    int *inc = malloc((size_t)n * sizeof(*inc));
    int *dec = malloc((size_t)n * sizeof(*dec));

    if (inc == NULL || dec == NULL) {
        free(inc);
        free(dec);
        return -1;
    }

    for (int i = 0; i < n; i++) {
        inc[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] > arr[j] && inc[i] < inc[j] + 1) {
                inc[i] = inc[j] + 1;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        dec[i] = 1;
        for (int j = n - 1; j > i; j--) {
            if (arr[i] > arr[j] && dec[i] < dec[j] + 1) {
                dec[i] = dec[j] + 1;
            }
        }
    }

    int max = 0;
    for (int i = 0; i < n; i++) {
        int length = inc[i] + dec[i] - 1;
        if (length > max) {
            max = length;
        }
    }

    free(inc);
    free(dec);

    return max;
}

int main(void) {
    int arr[] = {1, 11, 2, 10, 4, 5, 2, 1};
    int n = (int)(sizeof(arr) / sizeof(arr[0]));

    int result = longestBitonicSubsequence(arr, n);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%d\n", result);

    return 0;
}