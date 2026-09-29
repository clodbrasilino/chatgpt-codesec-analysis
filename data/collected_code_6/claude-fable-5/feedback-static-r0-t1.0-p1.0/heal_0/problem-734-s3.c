#include <stdio.h>
#include <stdlib.h>

long long sumOfSubarrayProducts(const int *arr, size_t n)
{
    long long result = 0;
    long long runningProduct = 0;
    size_t i;

    if (arr == NULL || n == 0)
    {
        return 0;
    }

    for (i = 0; i < n; i++)
    {
        runningProduct = (long long)arr[i] * (runningProduct + 1);
        result += runningProduct;
    }

    return result;
}

int main(void)
{
    int arr[] = {1, 2, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long answer;

    answer = sumOfSubarrayProducts(arr, n);

    if (printf("Sum of products of all subarrays: %lld\n", answer) < 0)
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}