#include <stdio.h>
#include <stdlib.h>

long long countOddXorPairs(const int *arr, size_t n)
{
    long long evenCount = 0;
    long long oddCount = 0;
    size_t i;

    if (arr == NULL || n == 0)
    {
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        if ((arr[i] & 1) == 0)
        {
            evenCount++;
        }
        else
        {
            oddCount++;
        }
    }

    return evenCount * oddCount;
}

int main(void)
{
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = countOddXorPairs(arr, n);

    if (printf("Number of pairs with odd XOR: %lld\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}