#include <stdio.h>
#include <stdlib.h>

long long count_odd_xor_pairs(const int *arr, size_t n)
{
    long long odd_count = 0;
    long long even_count = 0;
    size_t i;

    if (arr == NULL) {
        return 0;
    }

    for (i = 0; i < n; i++) {
        if ((arr[i] & 1) != 0) {
            odd_count++;
        } else {
            even_count++;
        }
    }

    return odd_count * even_count;
}

int main(void)
{
    int arr[] = {5, 4, 7, 2, 1};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    long long result;

    result = count_odd_xor_pairs(arr, n);

    if (printf("Count of pairs with odd XOR: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}