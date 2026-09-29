#include <stdio.h>
#include <stdlib.h>

static int find_last_removed_position(const int *arr, size_t n, int m)
{
    size_t i;
    size_t pos = 0;
    long max_steps = -1;

    if (arr == NULL || n == 0 || m <= 0) {
        return -1;
    }

    for (i = 0; i < n; i++) {
        long steps;

        if (arr[i] <= 0) {
            continue;
        }

        steps = ((long)arr[i] + (long)m - 1L) / (long)m;

        if (steps >= max_steps) {
            max_steps = steps;
            pos = i;
        }
    }

    if (max_steps < 0) {
        return -1;
    }

    return (int)(pos + 1U);
}

int main(void)
{
    int arr[] = { 2, 5, 4 };
    int m = 2;
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result;

    result = find_last_removed_position(arr, n, m);

    if (result < 0) {
        if (fprintf(stderr, "Error: invalid input to find_last_removed_position\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("Position of last removed element: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}