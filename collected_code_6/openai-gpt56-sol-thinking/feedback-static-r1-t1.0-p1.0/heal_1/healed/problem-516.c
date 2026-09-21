#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static unsigned int radix_key(int value)
{
    return (unsigned int)value - (unsigned int)INT_MIN;
}

int radix_sort(int *values, size_t count)
{
    int *buffer;
    int *source;
    int *destination;
    unsigned int bit_count = 0U;
    unsigned int shift = 0U;
    unsigned int limit;
    size_t allocation_size;
    size_t i;

    if (count != 0U && values == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (count < 2U) {
        return 0;
    }

    if (count > SIZE_MAX / sizeof(*buffer)) {
        errno = ENOMEM;
        return -1;
    }

    allocation_size = count * sizeof(*buffer);
    buffer = malloc(allocation_size);
    if (buffer == NULL) {
        errno = ENOMEM;
        return -1;
    }

    for (limit = UINT_MAX; limit != 0U; limit >>= 1U) {
        ++bit_count;
    }

    source = values;
    destination = buffer;

    for (;;) {
        size_t counts[16] = {0U};
        size_t total = 0U;
        int *temporary;

        for (i = 0U; i < count; ++i) {
            size_t digit =
                (size_t)((radix_key(source[i]) >> shift) & 0xFU);
            ++counts[digit];
        }

        for (i = 0U; i < 16U; ++i) {
            size_t frequency = counts[i];
            counts[i] = total;
            total += frequency;
        }

        for (i = 0U; i < count; ++i) {
            size_t digit =
                (size_t)((radix_key(source[i]) >> shift) & 0xFU);
            destination[counts[digit]] = source[i];
            ++counts[digit];
        }

        temporary = source;
        source = destination;
        destination = temporary;

        if (bit_count - shift <= 4U) {
            break;
        }

        shift += 4U;
    }

    if (source != values) {
        for (i = 0U; i < count; ++i) {
            values[i] = source[i];
        }
    }

    free(buffer);
    return 0;
}

int main(void)
{
    int values[] = {
        170, 45, 75, -90, 802, 24, 2, 66, 0, -1, INT_MAX, INT_MIN
    };
    size_t count = sizeof(values) / sizeof(values[0]);
    size_t i;

    if (radix_sort(values, count) != 0) {
        if (fprintf(stderr, "radix_sort failed: %s\n", strerror(errno)) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%d%s", values[i],
                   i + 1U == count ? "\n" : " ") < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}