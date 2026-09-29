#include <stdio.h>
#include <stdlib.h>

long long countOddXorPairs(const int *arr, size_t n)
{
    long long oddCount = 0;
    long long evenCount = 0;
    size_t i;

    if (arr == NULL || n == 0U)
    {
        return 0;
    }

    for (i = 0U; i < n; i++)
    {
        if ((arr[i] & 1) != 0)
        {
            oddCount++;
        }
        else
        {
            evenCount++;
        }
    }

    return oddCount * evenCount;
}

int main(void)
{
    int values[] = { 1, 2, 3, 4, 5 };
    size_t n = sizeof(values) / sizeof(values[0]);
    long long result;

    result = countOddXorPairs(values, n);

    if (printf("Number of pairs with odd XOR: %lld\n", result) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}