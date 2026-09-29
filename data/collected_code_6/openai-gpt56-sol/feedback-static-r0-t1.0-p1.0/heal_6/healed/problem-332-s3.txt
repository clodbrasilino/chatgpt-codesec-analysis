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
    if ((data == NULL && length != 0U) ||
        frequencies == NULL ||
        frequency_count < (size_t)UCHAR_MAX + 1U) {
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
    enum { INPUT_CAPACITY = 1024 };

    unsigned char input[INPUT_CAPACITY];
    size_t frequencies[(size_t)UCHAR_MAX + 1U];
    size_t length = 0U;
    int character;

    while (length < sizeof input) {
        character = fgetc(stdin);

        if (character == EOF) {
            if (ferror(stdin)) {
                return EXIT_FAILURE;
            }
            break;
        }

        input[length++] = (unsigned char)character;

        if (character == '\n') {
            break;
        }
    }

    if (length == sizeof input && input[length - 1U] != (unsigned char)'\n') {
        character = fgetc(stdin);

        if (character != EOF && character != '\n') {
            do {
                character = fgetc(stdin);
            } while (character != EOF && character != '\n');

            if (character == EOF && ferror(stdin)) {
                return EXIT_FAILURE;
            }

            return EXIT_FAILURE;
        }

        if (character == EOF && ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    if (count_character_frequency(
            input,
            length,
            frequencies,
            sizeof frequencies / sizeof frequencies[0]) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U;
         i < sizeof frequencies / sizeof frequencies[0];
         ++i) {
        if (frequencies[i] != 0U &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}