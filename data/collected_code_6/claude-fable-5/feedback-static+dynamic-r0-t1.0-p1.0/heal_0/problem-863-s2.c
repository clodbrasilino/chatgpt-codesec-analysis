#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int longest_consecutive_subsequence(const int *arr, size_t n)
{
    int *sorted = NULL;
    int longest = 0;
    int current = 0;
    size_t i = 0;

    if (arr == NULL || n == 0) {
        return 0;
    }

    sorted = malloc(n * sizeof(*sorted));
    if (sorted == NULL) {
        return -1;
    }

    memcpy(sorted, arr, n * sizeof(*sorted));
    qsort(sorted, n, sizeof(*sorted), compare_ints);

    longest = 1;
    current = 1;

    for (i = 1; i < n; i++) {
        if (sorted[i] == sorted[i - 1]) {
            continue;
        }
        if (sorted[i] == sorted[i - 1] + 1) {
            current++;
            if (current > longest) {
                longest = current;
            }
        } else {
            current = 1;
        }
    }

    free(sorted);
    return longest;
}

int main(void)
{
    int arr[] = {1, 9, 3, 10, 4, 20, 2};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result = 0;

    result = longest_consecutive_subsequence(arr, n);
    if (result < 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("Length of the longest consecutive subsequence: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}