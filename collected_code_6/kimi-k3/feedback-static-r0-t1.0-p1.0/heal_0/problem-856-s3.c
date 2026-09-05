#include <stdio.h>
#include <stdlib.h>

long min_swaps(const int *arr, size_t n)
{
    long swaps = 0;
    long ones = 0;
    size_t i;

    if (arr == NULL)
        return -1;

    for (i = 0; i < n; i++) {
        if (arr[i] == 1)
            ones++;
        else if (arr[i] == 0)
            swaps += ones;
        else
            return -1;
    }

    return swaps;
}

int main(void)
{
    int arr[] = {1, 0, 1, 0, 1, 0};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long result;

    result = min_swaps(arr, n);

    if (result >= 0)
        printf("Minimum adjacent swaps: %ld\n", result);
    else
        printf("Invalid input\n");

    return 0;
}