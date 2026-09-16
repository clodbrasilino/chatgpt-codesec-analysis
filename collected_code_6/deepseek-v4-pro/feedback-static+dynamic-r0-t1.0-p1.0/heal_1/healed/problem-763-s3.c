#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare_ints(const void *a, const void *b) {
    int arg1 = *(const int *)a;
    int arg2 = *(const int *)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

int min_difference(const int arr[], size_t size) {
    if (size < 2) {
        return -1;
    }

    int *sorted = malloc(size * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; i++) {
        sorted[i] = arr[i];
    }

    qsort(sorted, size, sizeof(int), compare_ints);

    int min_diff = INT_MAX;
    for (size_t i = 1; i < size; i++) {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    free(sorted);
    return min_diff;
}

int main(void) {
    int arr[] = {4, 2, 1, 5, 7, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = min_difference(arr, size);
    if (result >= 0) {
        printf("%d\n", result);
    }
    return 0;
}