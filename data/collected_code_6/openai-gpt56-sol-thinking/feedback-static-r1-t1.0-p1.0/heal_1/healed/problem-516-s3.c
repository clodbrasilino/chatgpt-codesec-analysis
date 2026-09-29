#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int radix_sort(int32_t *values, size_t count)
{
    if (count == 0U) {
        return 0;
    }

    if (values == NULL) {
        return -1;
    }

    if (count == 1U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        return -1;
    }

    int32_t *buffer = malloc(count * sizeof(*buffer));
    if (buffer == NULL) {
        return -1;
    }

    int32_t *source = values;
    int32_t *destination = buffer;

    for (unsigned int pass = 0U; pass < 4U; ++pass) {
        size_t frequencies[256] = {0U};
        size_t positions[256];
        const unsigned int shift = pass * 8U;

        for (size_t i = 0U; i < count; ++i) {
            const uint32_t key =
                (uint32_t)source[i] ^ UINT32_C(0x80000000);
            const uint32_t digit =
                (key >> shift) & UINT32_C(0xFF);

            ++frequencies[digit];
        }

        positions[0] = 0U;

        for (size_t i = 1U; i < 256U; ++i) {
            positions[i] = positions[i - 1U] + frequencies[i - 1U];
        }

        for (size_t i = 0U; i < count; ++i) {
            const uint32_t key =
                (uint32_t)source[i] ^ UINT32_C(0x80000000);
            const uint32_t digit =
                (key >> shift) & UINT32_C(0xFF);

            destination[positions[digit]] = source[i];
            ++positions[digit];
        }

        int32_t *temporary = source;
        source = destination;
        destination = temporary;
    }

    free(buffer);
    return 0;
}

int main(void)
{
    int32_t values[] = {
        170,
        45,
        75,
        -90,
        802,
        24,
        2,
        66,
        INT32_MIN,
        INT32_MAX,
        0,
        -1
    };

    const size_t count = sizeof(values) / sizeof(values[0]);

    if (radix_sort(values, count) != 0) {
        if (fprintf(stderr, "Unable to sort the values.\n") < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        const char separator = i + 1U == count ? '\n' : ' ';

        if (printf("%" PRId32 "%c", values[i], separator) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}