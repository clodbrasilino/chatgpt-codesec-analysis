#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(const int *arr, size_t n, int *result)
{
    size_t i;
    int acc;

    if (arr == NULL || result == NULL || n == 0U) {
        return -1;
    }

    acc = 0;
    for (i = 0U; i < n; i++) {
        acc ^= arr[i];
    }

    *result = acc;
    return 0;
}

int main(void)
{
    int arr[] = { 1, 2, 3, 2, 3, 1, 3 };
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int result = 0;

    if (find_odd_occurrence(arr, n, &result) != 0) {
        (void)fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("The number occurring an odd number of times is: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}