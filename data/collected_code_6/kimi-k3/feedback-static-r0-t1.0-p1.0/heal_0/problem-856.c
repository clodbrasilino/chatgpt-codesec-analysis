#include <stdio.h>
#include <stdlib.h>

long long min_adjacent_swaps_binary_sort(const int *arr, size_t n)
{
    size_t i;
    long long swaps = 0;
    size_t ones = 0;

    if (arr == NULL) {
        return -1;
    }

    for (i = 0; i < n; ++i) {
        if (arr[i] == 1) {
            ++ones;
        } else if (arr[i] == 0) {
            swaps += (long long)ones;
        } else {
            return -1;
        }
    }

    return swaps;
}

int main(void)
{
    int arr[] = {1, 0, 1, 0, 1, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result = min_adjacent_swaps_binary_sort(arr, n);

    if (result < 0) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);
    return EXIT_SUCCESS;
}