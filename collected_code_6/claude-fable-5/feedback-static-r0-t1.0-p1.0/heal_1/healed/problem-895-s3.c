#include <stdio.h>
#include <stdlib.h>

long long max_non_adjacent_sum(const int *arr, size_t n)
{
    long long incl;
    long long excl;
    size_t i;

    if (arr == NULL || n == 0U) {
        return 0LL;
    }

    incl = (long long)arr[0];
    excl = 0LL;

    for (i = 1U; i < n; i++) {
        const long long new_excl = (incl > excl) ? incl : excl;
        incl = excl + (long long)arr[i];
        excl = new_excl;
    }

    return (incl > excl) ? incl : excl;
}

int main(void)
{
    int arr1[] = {5, 5, 10, 100, 10, 5};
    int arr2[] = {3, 2, 7, 10};
    int arr3[] = {-1, -2, -3};
    long long result;

    result = max_non_adjacent_sum(arr1, sizeof(arr1) / sizeof(arr1[0]));
    if (printf("Maximum sum: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    result = max_non_adjacent_sum(arr2, sizeof(arr2) / sizeof(arr2[0]));
    if (printf("Maximum sum: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    result = max_non_adjacent_sum(arr3, sizeof(arr3) / sizeof(arr3[0]));
    if (printf("Maximum sum: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}