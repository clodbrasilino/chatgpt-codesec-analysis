#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return -1;
    }
    if (x > y) {
        return 1;
    }
    return 0;
}

static int min_difference(const int *arr, size_t n, int *result)
{
    int *copy = NULL;
    size_t i;
    long min_diff = LONG_MAX;

    if (arr == NULL || result == NULL || n < 2) {
        return -1;
    }

    copy = malloc(n * sizeof(*copy));
    if (copy == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        copy[i] = arr[i];
    }

    qsort(copy, n, sizeof(*copy), compare_ints);

    for (i = 1; i < n; i++) {
        long diff = (long)copy[i] - (long)copy[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    free(copy);

    if (min_diff > INT_MAX) {
        return -1;
    }

    *result = (int)min_diff;
    return 0;
}

int main(void)
{
    int arr[] = { 30, 5, 20, 9, 100, 7 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result = 0;

    if (min_difference(arr, n, &result) != 0) {
        fprintf(stderr, "Error: could not compute minimum difference\n");
        return EXIT_FAILURE;
    }

    if (printf("Minimum difference: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}