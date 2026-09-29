#include <stdio.h>
#include <stdlib.h>

int find_odd_occurrence(const int *arr, size_t size, int *result)
{
    size_t i;
    int xor_value;

    if (arr == NULL || result == NULL || size == 0U) {
        return -1;
    }

    xor_value = 0;
    for (i = 0U; i < size; i++) {
        xor_value ^= arr[i];
    }

    *result = xor_value;
    return 0;
}

int main(void)
{
    int arr[] = {2, 3, 5, 4, 5, 2, 4, 3, 5, 2, 4, 4, 2};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result;

    if (find_odd_occurrence(arr, size, &result) != 0) {
        if (fprintf(stderr, "Error: invalid input\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("The number occurring an odd number of times is: %d\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}