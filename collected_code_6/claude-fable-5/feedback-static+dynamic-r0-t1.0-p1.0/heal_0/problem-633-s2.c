#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t sum_xor_all_pairs(const int32_t *arr, size_t n)
{
    int64_t total = 0;

    if (arr == NULL || n < 2U) {
        return 0;
    }

    for (unsigned int bit = 0U; bit < 32U; bit++) {
        int64_t count_set = 0;

        for (size_t i = 0; i < n; i++) {
            uint32_t value = (uint32_t)arr[i];
            if (((value >> bit) & 1U) != 0U) {
                count_set++;
            }
        }

        int64_t count_unset = (int64_t)n - count_set;
        total += (count_set * count_unset) * ((int64_t)1 << bit);
    }

    return total;
}

int main(void)
{
    int32_t numbers[] = {7, 3, 5};
    size_t n = sizeof(numbers) / sizeof(numbers[0]);

    int64_t result = sum_xor_all_pairs(numbers, n);

    if (printf("Sum of XOR of all pairs: %lld\n", (long long)result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}