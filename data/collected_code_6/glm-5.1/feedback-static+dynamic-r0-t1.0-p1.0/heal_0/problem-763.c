#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int find_min_difference(int arr[], size_t n) {
    if (n < 2) {
        return -1;
    }

    qsort(arr, n, sizeof(int), compare);

    int min_diff = INT_MAX;

    for (size_t i = 1; i < n; i++) {
        int diff = arr[i] - arr[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    return min_diff;
}

int main(void) {
    int arr[] = {1, 5, 3, 19, 18, 25};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = find_min_difference(arr, n);

    printf("%d\n", result);

    return 0;
}