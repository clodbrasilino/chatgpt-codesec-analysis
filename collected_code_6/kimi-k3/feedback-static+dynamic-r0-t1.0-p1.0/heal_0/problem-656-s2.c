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

int find_min_sum_abs_diff(int arr1[], int arr2[], size_t n, long long *result)
{
    long long sum;
    size_t i;

    if (arr1 == NULL || arr2 == NULL || result == NULL || n == 0U) {
        return -1;
    }

    qsort(arr1, n, sizeof(arr1[0]), compare_ints);
    qsort(arr2, n, sizeof(arr2[0]), compare_ints);

    sum = 0LL;
    for (i = 0U; i < n; ++i) {
        long long diff = (long long)arr1[i] - (long long)arr2[i];
        if (diff < 0LL) {
            diff = -diff;
        }
        sum += diff;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    int arr1[] = {4, 1, 8, 7};
    int arr2[] = {2, 3, 6, 5};
    size_t n = sizeof(arr1) / sizeof(arr1[0]);
    long long result = 0LL;

    if (find_min_sum_abs_diff(arr1, arr2, n, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Minimum sum of absolute differences: %lld\n", result);
    return EXIT_SUCCESS;
}