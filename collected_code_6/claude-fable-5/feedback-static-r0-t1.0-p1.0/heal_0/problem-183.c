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

int count_pairs_with_diff_k(const int *arr, size_t n, int k, size_t *result)
{
    int *sorted;
    size_t i;
    size_t j;
    size_t count;

    if (arr == NULL || result == NULL || k < 0) {
        return -1;
    }

    *result = 0;

    if (n < 2) {
        return 0;
    }

    sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(*sorted), compare_ints);

    count = 0;
    i = 0;
    j = 1;

    while (i < n && j < n) {
        long diff;

        if (i == j) {
            j++;
            continue;
        }

        diff = (long)sorted[j] - (long)sorted[i];

        if (diff == (long)k) {
            count++;
            i++;
            j++;
            while (i < n && sorted[i] == sorted[i - 1]) {
                i++;
            }
            while (j < n && sorted[j] == sorted[j - 1]) {
                j++;
            }
        } else if (diff < (long)k) {
            j++;
        } else {
            i++;
        }
    }

    free(sorted);
    *result = count;
    return 0;
}

int main(void)
{
    int arr[] = {1, 5, 3, 4, 2, 3, 8};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int k = 3;
    size_t pairs = 0;

    if (count_pairs_with_diff_k(arr, n, k, &pairs) != 0) {
        fprintf(stderr, "Error counting pairs\n");
        return EXIT_FAILURE;
    }

    if (printf("Count of distinct pairs with difference %d is %zu\n", k, pairs) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}