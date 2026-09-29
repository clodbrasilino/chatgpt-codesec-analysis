#include <limits.h>
#include <stdint.h>
#include <stdio.h>

enum { CHARACTER_COUNT = UCHAR_MAX + 1 };

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t *frequencies,
    size_t frequency_count)
{
    if (data == NULL || frequencies == NULL ||
        frequency_count < CHARACTER_COUNT) {
        return -1;
    }

    for (size_t i = 0; i < frequency_count; ++i) {
        frequencies[i] = 0;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned int value = data[i];

        if (frequencies[value] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[value];
    }

    return 0;
}

int main(void)
{
    unsigned char input[1024];
    size_t frequencies[CHARACTER_COUNT];
    size_t length;

    if (fgets((char *)input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        input[0] = '\0';
    }

    for (length = 0; length < sizeof input && input[length] != '\0'; ++length) {
    }

    if (count_character_frequency(
            input,
            length,
            frequencies,
            sizeof frequencies / sizeof frequencies[0]) != 0) {
        return 1;
    }

    for (size_t i = 0; i < CHARACTER_COUNT; ++i) {
        if (frequencies[i] != 0 &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return 1;
        }
    }

    return 0;
}