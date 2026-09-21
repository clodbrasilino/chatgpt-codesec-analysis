#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    RADIX_SORT_OK = 0,
    RADIX_SORT_INVALID_ARGUMENT,
    RADIX_SORT_SIZE_OVERFLOW,
    RADIX_SORT_ALLOCATION_FAILURE
} RadixSortResult;

RadixSortResult radix_sort_int32(int32_t *array, size_t count)
{
    if (array == NULL) {
        return count == 0U ? RADIX_SORT_OK : RADIX_SORT_INVALID_ARGUMENT;
    }

    if (count < 2U) {
        return RADIX_SORT_OK;
    }

    if (count > SIZE_MAX / sizeof(*array)) {
        return RADIX_SORT_SIZE_OVERFLOW;
    }

    int32_t *temporary = malloc(count * sizeof(*temporary));
    if (temporary == NULL) {
        return RADIX_SORT_ALLOCATION_FAILURE;
    }

    int32_t *source = array;
    int32_t *destination = temporary;

    for (unsigned int shift = 0U; shift < 32U; shift += 8U) {
        size_t counts[256] = {0U};
        size_t positions[256];
        size_t total = 0U;

        for (size_t i = 0U; i < count; ++i) {
            const uint32_t key =
                (uint32_t)source[i] ^ UINT32_C(0x80000000);
            const size_t bucket =
                (size_t)((key >> shift) & UINT32_C(0xFF));

            ++counts[bucket];
        }

        for (size_t bucket = 0U; bucket < 256U; ++bucket) {
            positions[bucket] = total;
            total += counts[bucket];
        }

        for (size_t i = 0U; i < count; ++i) {
            const uint32_t key =
                (uint32_t)source[i] ^ UINT32_C(0x80000000);
            const size_t bucket =
                (size_t)((key >> shift) & UINT32_C(0xFF));

            destination[positions[bucket]++] = source[i];
        }

        int32_t *swap = source;
        source = destination;
        destination = swap;
    }

    free(temporary);
    return RADIX_SORT_OK;
}

static int write_int32(FILE *stream, int32_t value)
{
    if (stream == NULL) {
        return EOF;
    }

    return fprintf(stream, "%" PRId32, value) < 0 ? EOF : 0;
}

int main(void)
{
    int32_t values[] = {
        INT32_C(170),
        INT32_C(45),
        INT32_C(75),
        -INT32_C(90),
        -INT32_C(802),
        INT32_C(24),
        INT32_C(2),
        INT32_C(66),
        INT32_C(0),
        INT32_MAX,
        INT32_MIN
    };

    const size_t count = sizeof(values) / sizeof(values[0]);
    const RadixSortResult result = radix_sort_int32(values, count);

    if (result != RADIX_SORT_OK) {
        if (fputs("Radix sort failed\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (i != 0U && fputc(' ', stdout) == EOF) {
            return EXIT_FAILURE;
        }

        if (write_int32(stdout, values[i]) == EOF) {
            return EXIT_FAILURE;
        }
    }

    if (fputc('\n', stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}