#include <stdio.h>
#include <stdlib.h>

static int max_sum_repeated(const int *arr, size_t n, long long k, long long *result)
{
    size_t i;
    long long total;
    long long best;
    long long current;
    long long limit;
    long long j;

    if (arr == NULL || result == NULL || n == 0 || k <= 0) {
        return -1;
    }

    total = 0;
    for (i = 0; i < n; i++) {
        total += (long long)arr[i];
    }

    limit = (k >= 2) ? (long long)n * 2 : (long long)n;
    best = (long long)arr[0];
    current = 0;

    for (j = 0; j < limit; j++) {
        long long v = (long long)arr[(size_t)(j % (long long)n)];
        current += v;
        if (current > best) {
            best = current;
        }
        if (current < 0) {
            current = 0;
        }
    }

    if (k > 2 && total > 0) {
        best += (k - 2) * total;
    }

    *result = best;
    return 0;
}

int main(void)
{
    int arr1[] = {1, 2};
    int arr2[] = {1, -2, 1};
    int arr3[] = {-1, -2, -3};
    long long result;

    if (max_sum_repeated(arr1, sizeof(arr1) / sizeof(arr1[0]), 3, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Largest sum (arr1, k=3): %lld\n", result);

    if (max_sum_repeated(arr2, sizeof(arr2) / sizeof(arr2[0]), 5, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Largest sum (arr2, k=5): %lld\n", result);

    if (max_sum_repeated(arr3, sizeof(arr3) / sizeof(arr3[0]), 4, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }
    printf("Largest sum (arr3, k=4): %lld\n", result);

    return EXIT_SUCCESS;
}