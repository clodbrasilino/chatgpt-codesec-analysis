#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

static bool find_triplet(const int *arr, size_t n, long target,
                         int *out_a, int *out_b, int *out_c)
{
    int *sorted;
    size_t i;

    if (arr == NULL || n < 3U || out_a == NULL || out_b == NULL ||
        out_c == NULL) {
        return false;
    }

    sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return false;
    }

    for (i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(*sorted), compare_ints);

    for (i = 0; i + 2U < n; i++) {
        size_t left = i + 1U;
        size_t right = n - 1U;

        while (left < right) {
            long sum = (long)sorted[i] + (long)sorted[left] +
                       (long)sorted[right];

            if (sum == target) {
                *out_a = sorted[i];
                *out_b = sorted[left];
                *out_c = sorted[right];
                free(sorted);
                return true;
            }
            if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
    }

    free(sorted);
    return false;
}

int main(void)
{
    int arr[] = { 12, 3, 4, 1, 6, 9 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long target = 24;
    int a = 0;
    int b = 0;
    int c = 0;

    if (find_triplet(arr, n, target, &a, &b, &c)) {
        if (printf("Triplet found: %d, %d, %d\n", a, b, c) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (printf("No triplet found with sum %ld\n", target) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}