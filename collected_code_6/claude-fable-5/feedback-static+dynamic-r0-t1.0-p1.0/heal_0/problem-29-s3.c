#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(const int *arr, size_t size, int *result)
{
    size_t i;
    int xor_val;

    if (arr == NULL || result == NULL || size == 0U) {
        return -1;
    }

    xor_val = 0;
    for (i = 0U; i < size; i++) {
        xor_val ^= arr[i];
    }

    *result = xor_val;
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 2, 3, 1, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    if (find_odd_occurrence(arr, size, &result) != 0) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    if (printf("Element occurring odd number of times: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}