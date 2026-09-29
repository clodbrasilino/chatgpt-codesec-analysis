#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    uintmax_t *frequency,
    size_t frequency_size)
{
    if ((data == NULL && length != 0U) ||
        frequency == NULL ||
        frequency_size < (size_t)UCHAR_MAX + 1U) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        const size_t index = (size_t)data[i];

        if (frequency[index] == UINTMAX_MAX) {
            return -1;
        }

        ++frequency[index];
    }

    return 0;
}

int main(void)
{
    const size_t input_size = 4096U;
    const size_t frequency_size = (size_t)UCHAR_MAX + 1U;

    unsigned char *input = malloc(input_size);
    uintmax_t *frequency = calloc(frequency_size, sizeof *frequency);

    if (input == NULL || frequency == NULL) {
        free(input);
        free(frequency);
        fputs("Failed to allocate memory.\n", stderr);
        return 1;
    }

    for (;;) {
        const size_t bytes_read = fread(input, sizeof *input, input_size, stdin);

        if (count_character_frequency(
                input, bytes_read, frequency, frequency_size) != 0) {
            free(input);
            free(frequency);
            fputs("Frequency counter overflow.\n", stderr);
            return 1;
        }

        if (bytes_read < input_size) {
            if (ferror(stdin)) {
                free(input);
                free(frequency);
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            break;
        }
    }

    for (size_t i = 0U; i < frequency_size; ++i) {
        if (frequency[i] != UINTMAX_C(0) &&
            printf("0x%02jX: %ju\n", (uintmax_t)i, frequency[i]) < 0) {
            free(input);
            free(frequency);
            fputs("Failed to write output.\n", stderr);
            return 1;
        }
    }

    if (fflush(stdout) == EOF) {
        free(input);
        free(frequency);
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    free(input);
    free(frequency);
    return 0;
}