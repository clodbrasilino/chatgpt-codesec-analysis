#include <stdio.h>
#include <stdlib.h>

static int compare_ints(const void *a, const void *b)
{
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

static long long min_sum_abs_diff(int arr1[], int arr2[], size_t n)
{
    long long sum = 0;
    size_t i;

    qsort(arr1, n, sizeof(int), compare_ints);
    qsort(arr2, n, sizeof(int), compare_ints);

    for (i = 0; i < n; i++) {
        long long diff = (long long)arr1[i] - (long long)arr2[i];
        if (diff < 0) {
            diff = -diff;
        }
        sum += diff;
    }

    return sum;
}

int main(void)
{
    size_t n;
    size_t i;
    int *arr1 = NULL;
    int *arr2 = NULL;
    long long result;

    if (scanf("%zu", &n) != 1 || n == 0) {
        return EXIT_FAILURE;
    }

    arr1 = (int *)malloc(n * sizeof(int));
    arr2 = (int *)malloc(n * sizeof(int));

    if (arr1 == NULL || arr2 == NULL) {
        free(arr1);
        free(arr2);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr1[i]) != 1) {
            free(arr1);
            free(arr2);
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i < n; i++) {
        if (scanf("%d", &arr2[i]) != 1) {
            free(arr1);
            free(arr2);
            return EXIT_FAILURE;
        }
    }

    result = min_sum_abs_diff(arr1, arr2, n);

    printf("%lld\n", result);

    free(arr1);
    free(arr2);

    return EXIT_SUCCESS;
}