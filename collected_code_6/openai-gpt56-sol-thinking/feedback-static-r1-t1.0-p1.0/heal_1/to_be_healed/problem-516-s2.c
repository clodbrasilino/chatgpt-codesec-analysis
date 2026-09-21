#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    RADIX_SORT_OK = 0,
    RADIX_SORT_INVALID_ARGUMENT,
    RADIX_SORT_SIZE_OVERFLOW,
    RADIX_SORT_ALLOCATION_FAILURE
} RadixSortResult;

RadixSortResult radix_sort_int32(int32_t *array, size_t count)
{
    int32_t *temporary;
    int32_t *source;
    int32_t *destination;
    size_t allocation_size;

    if (array == NULL) {
        return count == 0U ? RADIX_SORT_OK : RADIX_SORT_INVALID_ARGUMENT;
    }

    if (count < 2U) {
        return RADIX_SORT_OK;
    }

    if (count > SIZE_MAX / sizeof(*array)) {
        return RADIX_SORT_SIZE_OVERFLOW;
    }

    allocation_size = count * sizeof(*array);
    temporary = malloc(allocation_size);

    if (temporary == NULL) {
        return RADIX_SORT_ALLOCATION_FAILURE;
    }

    source = array;
    destination = temporary;

    for (unsigned int shift = 0U; shift < 32U; shift += 8U) {
        size_t counts[256] = {0U};
        size_t positions[256];
        size_t total = 0U;

        for (size_t i = 0U; i < count; ++i) {
            uint32_t key = (uint32_t)source[i] ^ UINT32_C(0x80000000);
            size_t bucket = (size_t)((key >> shift) & UINT32_C(0xFF));

            ++counts[bucket];
        }

        for (size_t i = 0U; i < 256U; ++i) {
            positions[i] = total;
            total += counts[i];
        }

        for (size_t i = 0U; i < count; ++i) {
            uint32_t key = (uint32_t)source[i] ^ UINT32_C(0x80000000);
            size_t bucket = (size_t)((key >> shift) & UINT32_C(0xFF));

            destination[positions[bucket]++] = source[i];
        }

        {
            int32_t *swap = source;
            source = destination;
            destination = swap;
        }
    }

    if (source != array) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(array, source, allocation_size);
    }

    free(temporary);
    return RADIX_SORT_OK;
}

int main(void)
{
    int32_t values[] = {
        170, 45, 75, -90, -802, 24, 2, 66, 0, INT32_MAX, INT32_MIN
    };
    const size_t count = sizeof(values) / sizeof(values[0]);
    RadixSortResult result = radix_sort_int32(values, count);

    if (result != RADIX_SORT_OK) {
        fprintf(stderr, "Radix sort failed with error code %d\n", (int)result);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s%ld", i == 0U ? "" : " ", (long)values[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    if (putchar('\n') == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}