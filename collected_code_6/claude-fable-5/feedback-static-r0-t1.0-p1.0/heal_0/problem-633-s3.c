#include <stdio.h>
#include <stdlib.h>

long long sum_xor_all_pairs(const int *arr, size_t n)
{
    long long total = 0;
    int bit;

    if (arr == NULL || n < 2) {
        return 0;
    }

    for (bit = 0; bit < 32; bit++) {
        long long count_set = 0;
        size_t i;

        for (i = 0; i < n; i++) {
            if ((arr[i] >> bit) & 1) {
                count_set++;
            }
        }

        total += count_set * (long long)(n - count_set) * (1LL << bit);
    }

    return total;
}

int main(void)
{
    int numbers[] = {7, 3, 5};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);
    long long result;

    result = sum_xor_all_pairs(numbers, n);

    if (printf("Sum of XOR of all pairs: %lld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}