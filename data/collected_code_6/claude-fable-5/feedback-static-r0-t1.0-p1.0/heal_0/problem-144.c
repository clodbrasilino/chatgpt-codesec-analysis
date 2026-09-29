#include <stdio.h>
#include <stdlib.h>

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

static int sum_abs_differences(const int *arr, size_t n, long long *result)
{
    int *copy;
    size_t i;
    long long total;
    long long prefix;

    if (arr == NULL || result == NULL || n == 0) {
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

    total = 0;
    prefix = 0;
    for (i = 0; i < n; i++) {
        total += (long long)copy[i] * (long long)i - prefix;
        prefix += (long long)copy[i];
    }

    free(copy);
    *result = total;
    return 0;
}

int main(void)
{
    int arr[] = {1, 8, 9, 15, 16};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    if (sum_abs_differences(arr, n, &result) != 0) {
        fprintf(stderr, "Error computing sum of absolute differences\n");
        return EXIT_FAILURE;
    }

    printf("Sum of absolute differences: %lld\n", result);
    return EXIT_SUCCESS;
}