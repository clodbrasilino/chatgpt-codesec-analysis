#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { CHARACTER_COUNT = UCHAR_MAX + 1 };

static int count_character_frequency(
    FILE *stream,
    size_t *frequencies,
    size_t frequency_count)
{
    if (stream == NULL ||
        frequencies == NULL ||
        frequency_count < CHARACTER_COUNT) {
        return -1;
    }

    for (size_t i = 0; i < CHARACTER_COUNT; ++i) {
        frequencies[i] = 0;
    }

    size_t buffer_size = BUFSIZ;
    unsigned char *buffer = malloc(buffer_size);

    if (buffer == NULL) {
        return -1;
    }

    int result = 0;

    for (;;) {
        size_t bytes_read = fread(buffer, 1, buffer_size, stream);

        for (size_t i = 0; i < bytes_read; ++i) {
            size_t value = buffer[i];

            if (value >= frequency_count || frequencies[value] == SIZE_MAX) {
                result = -1;
                goto cleanup;
            }

            ++frequencies[value];
        }

        if (bytes_read < buffer_size) {
            if (ferror(stream)) {
                result = -1;
                goto cleanup;
            }

            if (feof(stream)) {
                break;
            }
        }
    }

cleanup:
    free(buffer);
    return result;
}

int main(void)
{
    size_t frequencies[CHARACTER_COUNT];

    if (count_character_frequency(
            stdin,
            frequencies,
            sizeof frequencies / sizeof frequencies[0]) != 0) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < CHARACTER_COUNT; ++i) {
        if (frequencies[i] != 0 &&
            printf("%u: %zu\n", (unsigned int)i, frequencies[i]) < 0) {
            return EXIT_FAILURE;
        }
    }

    return fflush(stdout) == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
}