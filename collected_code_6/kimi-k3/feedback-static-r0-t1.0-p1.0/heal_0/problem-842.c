#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int find_odd_occurrence(const int *arr, size_t size, int *result)
{
    int xor_result = 0;
    size_t i;

    if (arr == NULL || result == NULL || size == 0 || size > (SIZE_MAX / sizeof(int)))
    {
        return -1;
    }

    for (i = 0; i < size; i++)
    {
        xor_result ^= arr[i];
    }

    *result = xor_result;
    return 0;
}

int main(void)
{
    int arr[] = {1, 2, 3, 2, 3, 1, 3};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    int result = 0;
    int status;

    status = find_odd_occurrence(arr, size, &result);

    if (status == 0)
    {
        printf("Number occurring odd number of times: %d\n", result);
    }
    else
    {
        fprintf(stderr, "Error: Invalid input parameters\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}