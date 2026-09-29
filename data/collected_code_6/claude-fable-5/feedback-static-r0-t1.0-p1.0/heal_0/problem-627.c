#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int find_smallest_missing(const int *arr, size_t n, int *result)
{
    bool *seen = NULL;
    size_t i;
    int candidate;

    if (arr == NULL || result == NULL || n == 0) {
        return -1;
    }

    seen = calloc(n + 1U, sizeof(bool));
    if (seen == NULL) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        if (arr[i] >= 0 && (size_t)arr[i] <= n) {
            seen[arr[i]] = true;
        }
    }

    candidate = 0;
    for (i = 0; i <= n; i++) {
        if (!seen[i]) {
            candidate = (int)i;
            break;
        }
    }

    free(seen);
    seen = NULL;

    *result = candidate;
    return 0;
}

int main(void)
{
    int arr[] = {0, 1, 2, 6, 9, 11, 15};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int missing = 0;

    if (find_smallest_missing(arr, n, &missing) != 0) {
        fprintf(stderr, "Error: could not compute smallest missing number\n");
        return EXIT_FAILURE;
    }

    if (printf("Smallest missing number: %d\n", missing) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}