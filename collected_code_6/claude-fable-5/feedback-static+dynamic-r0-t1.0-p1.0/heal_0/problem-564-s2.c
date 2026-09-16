#include <stdio.h>
#include <stdlib.h>

unsigned long long count_unequal_pairs(const int *arr, size_t n)
{
    unsigned long long count = 0ULL;
    size_t i;
    size_t j;

    if (arr == NULL || n < 2U) {
        return 0ULL;
    }

    for (i = 0U; i < n - 1U; i++) {
        for (j = i + 1U; j < n; j++) {
            if (arr[i] != arr[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    int data[] = { 1, 2, 1, 3, 2, 4 };
    size_t n = sizeof(data) / sizeof(data[0]);
    unsigned long long result;

    result = count_unequal_pairs(data, n);

    if (printf("Number of unequal pairs: %llu\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}