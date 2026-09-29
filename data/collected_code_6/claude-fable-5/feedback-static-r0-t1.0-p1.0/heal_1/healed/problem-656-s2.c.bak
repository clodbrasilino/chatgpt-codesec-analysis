#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int min_abs_diff_sum(const int *arr1, const int *arr2, size_t n, long long *result)
{
    int *a;
    int *b;
    size_t i;
    long long sum;

    if (arr1 == NULL || arr2 == NULL || result == NULL || n == 0) {
        return -1;
    }

    a = malloc(n * sizeof(*a));
    if (a == NULL) {
        return -1;
    }

    b = malloc(n * sizeof(*b));
    if (b == NULL) {
        free(a);
        return -1;
    }

    memcpy(a, arr1, n * sizeof(*a));
    memcpy(b, arr2, n * sizeof(*b));

    qsort(a, n, sizeof(*a), compare_ints);
    qsort(b, n, sizeof(*b), compare_ints);

    sum = 0;
    for (i = 0; i < n; i++) {
        long long diff = (long long)a[i] - (long long)b[i];
        if (diff < 0) {
            diff = -diff;
        }
        sum += diff;
    }

    free(a);
    free(b);

    *result = sum;
    return 0;
}

int main(void)
{
    const int arr1[] = {4, 1, 8, 7};
    const int arr2[] = {2, 3, 6, 5};
    size_t n = sizeof(arr1) / sizeof(arr1[0]);
    long long result;

    if (min_abs_diff_sum(arr1, arr2, n, &result) != 0) {
        fprintf(stderr, "Error computing minimum sum\n");
        return EXIT_FAILURE;
    }

    printf("Minimum sum of absolute differences: %lld\n", result);
    return EXIT_SUCCESS;
}