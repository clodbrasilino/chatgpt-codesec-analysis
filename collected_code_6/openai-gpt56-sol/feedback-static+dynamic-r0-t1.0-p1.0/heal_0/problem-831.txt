#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int count_equal_pairs(const int *array, size_t length, uint64_t *result)
{
    uint64_t count = 0;

    if (result == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        for (size_t j = i + 1U; j < length; ++j) {
            if (array[i] == array[j]) {
                if (count == UINT64_MAX) {
                    return -1;
                }
                ++count;
            }
        }
    }

    *result = count;
    return 0;
}

int main(void)
{
    const int array[] = {1, 2, 3, 1, 2, 1};
    const size_t length = sizeof(array) / sizeof(array[0]);
    uint64_t pair_count = 0;

    if (count_equal_pairs(array, length, &pair_count) != 0) {
        fputs("Failed to count equal pairs.\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", pair_count) < 0) {
        return 1;
    }

    return 0;
}