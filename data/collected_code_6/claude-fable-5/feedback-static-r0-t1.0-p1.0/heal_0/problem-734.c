#include <stdio.h>
#include <stddef.h>

long long sum_of_subarray_products(const int *arr, size_t n)
{
    long long total = 0;
    long long cur = 0;
    size_t i;

    if (arr == NULL || n == 0) {
        return 0;
    }

    for (i = n; i > 0; i--) {
        cur = (long long)arr[i - 1] * (1LL + cur);
        total += cur;
    }

    return total;
}

int main(void)
{
    int arr[] = {1, 2, 3};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = sum_of_subarray_products(arr, n);

    if (printf("Sum of products of all subarrays: %lld\n", result) < 0) {
        return 1;
    }

    return 0;
}