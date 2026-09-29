#include <stdio.h>
#include <stdlib.h>

static long count_equal_pairs(const int *arr, size_t n)
{
    long count = 0;
    size_t i;
    size_t j;

    if (arr == NULL || n < 2U) {
        return 0;
    }

    for (i = 0; i < n - 1U; i++) {
        for (j = i + 1U; j < n; j++) {
            if (arr[i] == arr[j]) {
                count++;
            }
        }
    }

    return count;
}

int main(void)
{
    int data[] = {1, 5, 1, 3, 5, 1, 7};
    size_t n = sizeof(data) / sizeof(data[0]);
    long result;

    result = count_equal_pairs(data, n);

    if (printf("Number of equal element pairs: %ld\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}