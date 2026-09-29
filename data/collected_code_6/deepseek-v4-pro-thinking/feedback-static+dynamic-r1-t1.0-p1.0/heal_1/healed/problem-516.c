#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int radix_sort(unsigned int *array, size_t length)
{
    size_t i, shift;
    unsigned int digit;
    size_t count[UCHAR_MAX + 1U];
    unsigned int *buffer, *temp, *src, *dst;
    int passes;
    size_t total_bits;

    if (array == NULL) return -1;
    if (length < 2) return 0;
    if (length > SIZE_MAX / sizeof(*array)) return -1;

    buffer = malloc(length * sizeof(*array));
    if (buffer == NULL) return -1;

    total_bits = sizeof(*array) * CHAR_BIT;
    passes = (int)(total_bits / CHAR_BIT);

    src = array;
    dst = buffer;

    for (shift = 0; shift < total_bits; shift += CHAR_BIT) {
        memset(count, 0, sizeof(count));
        for (i = 0; i < length; ++i) {
            digit = (src[i] >> shift) & (unsigned int)UCHAR_MAX;
            ++count[digit];
        }
        for (i = 1; i <= (size_t)UCHAR_MAX; ++i) {
            count[i] += count[i - 1];
        }
        for (i = length; i > 0; --i) {
            digit = (src[i - 1] >> shift) & (unsigned int)UCHAR_MAX;
            dst[count[digit] - 1] = src[i - 1];
            --count[digit];
        }
        temp = src;
        src = dst;
        dst = temp;
    }

    if (passes % 2 == 1) {
        for (i = 0; i < length; ++i) {
            array[i] = buffer[i];
        }
    }

    free(buffer);
    return 0;
}

int main(void)
{
    unsigned int values[] = { 170U, 45U, 75U, 90U, 802U, 24U, 2U, 66U };
    size_t length = sizeof(values) / sizeof(values[0]);
    size_t i;

    if (radix_sort(values, length) != 0) {
        fprintf(stderr, "Error: sorting failed\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < length; ++i) {
        printf("%u ", values[i]);
    }
    printf("\n");

    return EXIT_SUCCESS;
}