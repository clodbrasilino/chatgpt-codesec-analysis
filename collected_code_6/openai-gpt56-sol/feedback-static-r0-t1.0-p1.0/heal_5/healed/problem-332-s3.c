#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t frequencies[static UCHAR_MAX + 1U])
{
    if ((data == NULL && length != 0U) || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0U; i <= (size_t)UCHAR_MAX; ++i) {
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
    enum { INPUT_CAPACITY = 1024 };
    unsigned char input[INPUT_CAPACITY];
    size_t frequencies[UCHAR_MAX + 1U];
    size_t length = 0U;

    while (length < sizeof input) {
        int character = fgetc(stdin);

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

    if (length == sizeof input) {
        int character = fgetc(stdin);

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

    if (count_character_frequency(input, length, frequencies) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i <= (size_t)UCHAR_MAX; ++i) {
        if (frequencies[i] != 0U &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}