#include <stdio.h>
#include <stdlib.h>

size_t count_equal_pairs(const int *arr, size_t n)
{
    size_t count = 0;
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
    int data[] = {1, 2, 3, 1, 2, 1, 4};
    size_t n = sizeof(data) / sizeof(data[0]);
    size_t pairs;

    pairs = count_equal_pairs(data, n);

    if (printf("Number of equal element pairs: %zu\n", pairs) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}