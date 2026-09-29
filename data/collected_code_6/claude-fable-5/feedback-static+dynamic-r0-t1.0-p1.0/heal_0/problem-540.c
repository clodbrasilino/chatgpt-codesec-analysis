#include <stdio.h>
#include <stdlib.h>

int findDiff(const int *arr, size_t n)
{
    if (arr == NULL || n == 0) {
        return 0;
    }

    size_t *counts = calloc(n, sizeof(size_t));
    if (counts == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; i++) {
        size_t j;
        int found = 0;
        for (j = 0; j < i; j++) {
            if (arr[j] == arr[i]) {
                found = 1;
                break;
            }
        }
        if (found) {
            counts[j]++;
        } else {
            counts[i] = 1;
        }
    }

    size_t maxFreq = 0;
    size_t minFreq = n + 1;

    for (size_t i = 0; i < n; i++) {
        if (counts[i] > 0) {
            if (counts[i] > maxFreq) {
                maxFreq = counts[i];
            }
            if (counts[i] < minFreq) {
                minFreq = counts[i];
            }
        }
    }

    free(counts);

    if (minFreq > maxFreq) {
        return 0;
    }

    return (int)(maxFreq - minFreq);
}

int main(void)
{
    int arr[] = {1, 1, 2, 2, 7, 8, 4, 5, 1, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = findDiff(arr, n);

    if (printf("Difference between highest and least frequencies: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}