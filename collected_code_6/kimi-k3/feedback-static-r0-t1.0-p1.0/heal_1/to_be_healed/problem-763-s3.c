#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_min_difference(const int *arr, size_t n) {
    if (arr == NULL || n < 2) {
        return -1;
    }

    int *sorted = (int *)malloc(n * sizeof(int));
    if (sorted == NULL) {
        return -1;
    }

    for (size_t i = 0; i < n; i++) {
        sorted[i] = arr[i];
    }

    /* Possible weaknesses found:
     *  function definition is not allowed here
     */
    int compare(const void *a, const void *b) {
        int x = *(const int *)a;
        int y = *(const int *)b;
        if (x < y) return -1;
        if (x > y) return 1;
        return 0;
    }

    /* Possible weaknesses found:
     *  use of undeclared identifier 'compare'
     */
    qsort(sorted, n, sizeof(int), compare);

    int min_diff = INT_MAX;
    for (size_t i = 1; i < n; i++) {
        int diff = sorted[i] - sorted[i - 1];
        if (diff < min_diff) {
            min_diff = diff;
        }
    }

    free(sorted);
    return min_diff;
}

int main(void) {
    int arr[] = {5, 3, 19, 7, 2, 11};
    size_t n = sizeof(arr) / sizeof(arr[0]);

    int result = find_min_difference(arr, n);
    if (result >= 0) {
        printf("Minimum difference: %d\n", result);
    } else {
        printf("Invalid input or insufficient elements.\n");
    }

    return 0;
}