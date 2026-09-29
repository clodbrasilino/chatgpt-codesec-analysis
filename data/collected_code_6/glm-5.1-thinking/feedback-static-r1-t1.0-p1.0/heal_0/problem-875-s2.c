#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    int ia = *(const int *)a;
    int ib = *(const int *)b;
    return (ia > ib) - (ia < ib);
}

int find_min_difference(const int *arr, size_t n, int *result) {
    if (arr == NULL || result == NULL || n < 2) {
        return -1;
    }

    int *sorted = malloc(n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }

    for (size_t i = 0; i < n; ++i) {
        sorted[i] = arr[i];
    }

    qsort(sorted, n, sizeof(int), compare);

    int min_diff = INT_MAX;
    for (size_t i = 1; i < n; ++i) {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    free(sorted);
    *result = min_diff;
    return 0;
}

int main(void) {
    int tuples[] = {1, 5, 3, 19, 18, 25};
    size_t n = sizeof(tuples) / sizeof(tuples[0]);
    int min_diff;

    if (find_min_difference(tuples, n, &min_diff) == 0) {
        printf("%d\n", min_diff);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}