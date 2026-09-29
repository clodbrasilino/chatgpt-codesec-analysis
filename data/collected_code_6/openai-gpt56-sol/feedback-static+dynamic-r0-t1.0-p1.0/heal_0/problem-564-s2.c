#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int count_unequal_pairs(const int *array, size_t length, uint64_t *count)
{
    uint64_t total_pairs;
    uint64_t equal_pairs = 0U;

    if (count == NULL || (array == NULL && length != 0U)) {
        return -1;
    }

    if (length > UINT64_MAX) {
        return -1;
    }

    total_pairs = ((uint64_t)length * ((uint64_t)length - (length != 0U ? 1U : 0U))) / 2U;

    for (size_t i = 0U; i < length; ++i) {
        for (size_t j = i + 1U; j < length; ++j) {
            if (array[i] == array[j]) {
                ++equal_pairs;
            }
        }
    }

    *count = total_pairs - equal_pairs;
    return 0;
}

int main(void)
{
    int array[] = {1, 2, 1, 3, 2};
    size_t length = sizeof(array) / sizeof(array[0]);
    uint64_t count = 0U;

    if (count_unequal_pairs(array, length, &count) != 0) {
        fputs("Failed to count unequal pairs.\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return 1;
    }

    return 0;
}