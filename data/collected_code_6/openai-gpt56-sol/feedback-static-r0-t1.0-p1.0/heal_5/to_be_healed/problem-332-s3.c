#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t *frequencies,
    size_t frequency_count)
{
    const size_t required_count = (size_t)UCHAR_MAX + 1U;

    if ((data == NULL && length != 0U) ||
        frequencies == NULL ||
        frequency_count < required_count) {
        return -1;
    }

    for (size_t i = 0U; i < frequency_count; ++i) {
        frequencies[i] = 0U;
    }

    for (size_t i = 0U; i < length; ++i) {
        const size_t value = (size_t)data[i];

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    return 0;
}

int main(void)
{
    enum { INPUT_CAPACITY = 1024 };
    const size_t frequency_count = (size_t)UCHAR_MAX + 1U;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_CAPACITY];
    size_t frequencies[UCHAR_MAX + 1U];
    size_t length = 0U;
    int status = EXIT_FAILURE;

    while (length < sizeof(input)) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int character = getchar();

        if (character == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        input[length] = (unsigned char)character;
        ++length;

        if (character == '\n') {
            break;
        }
    }

    if (count_character_frequency(
            input, length, frequencies, frequency_count) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < frequency_count; ++i) {
        if (frequencies[i] != 0U) {
            if (printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    status = EXIT_SUCCESS;
    return status;
}