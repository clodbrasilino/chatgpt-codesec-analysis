#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

static int compare_ints(const void *a, const void *b)
{
    int int_a = *(const int *)a;
    int int_b = *(const int *)b;

    if (int_a < int_b) {
        return -1;
    }
    if (int_a > int_b) {
        return 1;
    }
    return 0;
}

int min_subsets_distinct(const int *arr, size_t n)
{
    int *sorted;
    size_t i;
    size_t bytes_to_copy;
    int max_frequency = 0;
    int current_frequency = 1;

    if (arr == NULL) {
        return -1;
    }

    if (n == 0) {
        return 0;
    }

    if (n > SIZE_MAX / sizeof(int)) {
        return -1;
    }

    bytes_to_copy = n * sizeof(int);

    if (bytes_to_copy > INT_MAX) {
        return -1;
    }

    sorted = (int *)malloc(bytes_to_copy);
    if (sorted == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(sorted, arr, bytes_to_copy);

    qsort(sorted, n, sizeof(int), compare_ints);

    for (i = 1; i < n; ++i) {
        if (sorted[i] == sorted[i - 1]) {
            ++current_frequency;
        } else {
            if (current_frequency > max_frequency) {
                max_frequency = current_frequency;
            }
            current_frequency = 1;
        }
    }

    if (current_frequency > max_frequency) {
        max_frequency = current_frequency;
    }

    free(sorted);
    sorted = NULL;

    return max_frequency;
}

int main(void)
{
    int arr[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = min_subsets_distinct(arr, n);

    if (result < 0) {
        fprintf(stderr, "Error: invalid input or memory allocation failure\n");
        return EXIT_FAILURE;
    }

    printf("Minimum number of subsets with distinct elements: %d\n", result);

    return EXIT_SUCCESS;
}