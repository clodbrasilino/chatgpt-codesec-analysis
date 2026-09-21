#include <limits.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t *frequencies,
    size_t frequency_count)
{
    if (data == NULL || frequencies == NULL ||
        frequency_count < (size_t)UCHAR_MAX + 1U) {
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
    size_t frequencies[(size_t)UCHAR_MAX + 1U];
    size_t length = 0;
    int character;

    while (length < sizeof input && (character = getchar()) != EOF) {
        input[length++] = (unsigned char)character;

        if (character == '\n') {
            break;
        }
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (count_character_frequency(
            input,
            length,
            frequencies,
            sizeof frequencies / sizeof frequencies[0]) != 0) {
        return 1;
    }

    for (size_t i = 0; i < sizeof frequencies / sizeof frequencies[0]; ++i) {
        if (frequencies[i] != 0 &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return 1;
        }
    }

    return 0;
}