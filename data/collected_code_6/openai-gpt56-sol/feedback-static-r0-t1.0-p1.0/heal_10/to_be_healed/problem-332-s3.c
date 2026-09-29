#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define SYMBOL_COUNT ((size_t)UCHAR_MAX + 1U)
#define INPUT_CAPACITY 1024U

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t *frequencies,
    size_t frequency_count)
{
    if ((data == NULL && length != 0U) ||
        frequencies == NULL ||
        frequency_count < SYMBOL_COUNT) {
        return -1;
    }

    for (size_t i = 0U; i < frequency_count; ++i) {
        frequencies[i] = 0U;
    }

    for (size_t i = 0U; i < length; ++i) {
        const size_t value = data[i];

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_CAPACITY];
    size_t frequencies[SYMBOL_COUNT];
    size_t length = 0U;
    int character;
    int too_long = 0;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF) {
        if (character == '\n') {
            break;
        }

        if (length < sizeof input) {
            input[length++] = (unsigned char)character;
        } else {
            too_long = 1;
        }
    }

    if (ferror(stdin) || too_long) {
        return EXIT_FAILURE;
    }

    if (count_character_frequency(
            input, length, frequencies, SYMBOL_COUNT) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < SYMBOL_COUNT; ++i) {
        if (frequencies[i] != 0U &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}