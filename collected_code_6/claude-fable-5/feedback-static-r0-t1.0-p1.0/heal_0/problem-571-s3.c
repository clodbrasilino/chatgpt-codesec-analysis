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

static long long max_sum_disjoint_pairs(const int *arr, size_t n, int k)
{
    int *sorted;
    long long sum = 0LL;
    size_t i;

    if (arr == NULL || n < 2U) {
        return 0LL;
    }

    sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return -1LL;
    }

    for (i = 0U; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(*sorted), compare_ints);

    i = n - 1U;
    while (i > 0U) {
        if (sorted[i] - sorted[i - 1U] < k) {
            sum += (long long)sorted[i] + (long long)sorted[i - 1U];
            if (i < 2U) {
                break;
            }
            i -= 2U;
        } else {
            i -= 1U;
        }
    }

    free(sorted);
    return sum;
}

int main(void)
{
    int arr[] = {3, 5, 10, 15, 17, 12, 9};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 4;
    long long result;

    result = max_sum_disjoint_pairs(arr, n, k);
    if (result < 0LL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Maximum sum of disjoint pairs: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}