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
        size_t value = (size_t)data[i];

        if (value >= frequency_count || frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    return 0;
}

int main(void)
{
    unsigned char input[INPUT_CAPACITY];
    size_t frequencies[SYMBOL_COUNT];
    size_t length = 0U;
    int character;
    int line_complete = 0;

    while (length < INPUT_CAPACITY) {
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }

            line_complete = 1;
            break;
        }

        if (character == '\n') {
            line_complete = 1;
            break;
        }

        input[length++] = (unsigned char)character;
    }

    if (!line_complete) {
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
        } else {
            while (character != '\n') {
                character = fgetc(stdin);

                if (character == EOF) {
                    if (ferror(stdin)) {
                        return EXIT_FAILURE;
                    }
                    break;
                }
            }

            return EXIT_FAILURE;
        }
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