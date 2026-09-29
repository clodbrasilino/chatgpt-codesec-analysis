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
    size_t frequencies[static SYMBOL_COUNT])
{
    if ((data == NULL && length != 0U) || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < SYMBOL_COUNT; ++i) {
        frequencies[i] = 0U;
    }

    for (size_t i = 0U; i < length; ++i) {
        size_t value = (size_t)data[i];

        if (frequencies[value] == SIZE_MAX) {
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

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length == INPUT_CAPACITY) {
            do {
                character = fgetc(stdin);
            } while (character != EOF && character != '\n');

            return EXIT_FAILURE;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (count_character_frequency(input, length, frequencies) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < SYMBOL_COUNT; ++i) {
        if (frequencies[i] != 0U) {
            if (printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}