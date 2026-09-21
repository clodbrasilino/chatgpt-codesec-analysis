#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int radix_sort(int32_t *values, size_t count)
{
    int32_t *buffer;
    int32_t *source;
    int32_t *destination;

    if (count == 0U) {
        return 0;
    }

    if (values == NULL) {
        return -1;
    }

    if (count == 1U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*buffer)) {
        return -1;
    }

    buffer = malloc(count * sizeof(*buffer));
    if (buffer == NULL) {
        return -1;
    }

    source = values;
    destination = buffer;

    for (unsigned int pass = 0U; pass < 4U; ++pass) {
        size_t frequencies[256] = {0U};
        size_t positions[256];
        const unsigned int shift = pass * 8U;

        for (size_t i = 0U; i < count; ++i) {
            const uint32_t key =
                ((uint32_t)source[i]) ^ UINT32_C(0x80000000);
            const uint32_t digit = (key >> shift) & UINT32_C(0xFF);

            ++frequencies[digit];
        }

        positions[0] = 0U;
        for (size_t i = 1U; i < 256U; ++i) {
            positions[i] = positions[i - 1U] + frequencies[i - 1U];
        }

        for (size_t i = 0U; i < count; ++i) {
            const uint32_t key =
                ((uint32_t)source[i]) ^ UINT32_C(0x80000000);
            const uint32_t digit = (key >> shift) & UINT32_C(0xFF);

            destination[positions[digit]++] = source[i];
        }

        {
            int32_t *temporary = source;
            source = destination;
            destination = temporary;
        }
    }

    if (source != values) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(values, source, count * sizeof(*values));
    }

    free(buffer);
    return 0;
}

int main(void)
{
    int32_t values[] = {
        170, 45, 75, -90, 802, 24, 2, 66, INT32_MIN, INT32_MAX, 0, -1
    };
    const size_t count = sizeof(values) / sizeof(values[0]);

    if (radix_sort(values, count) != 0) {
        if (fprintf(stderr, "Unable to sort the values.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        const char separator = (i + 1U == count) ? '\n' : ' ';

        if (printf("%" PRId32 "%c", values[i], separator) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}