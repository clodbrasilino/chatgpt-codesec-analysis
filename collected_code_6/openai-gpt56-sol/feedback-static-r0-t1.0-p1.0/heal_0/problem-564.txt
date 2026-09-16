#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

static int count_unequal_pairs(const int *array, size_t length, uint64_t *result)
{
    uint64_t count = 0;

    if (result == NULL || (array == NULL && length != 0)) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (array[i] != array[j]) {
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
    const int array[] = {1, 2, 1, 3, 2};
    const size_t length = sizeof(array) / sizeof(array[0]);
    uint64_t count = 0;

    if (count_unequal_pairs(array, length, &count) != 0) {
        fputs("Failed to count unequal pairs.\n", stderr);
        return 1;
    }

    if (printf("%" PRIu64 "\n", count) < 0) {
        return 1;
    }

    return 0;
}