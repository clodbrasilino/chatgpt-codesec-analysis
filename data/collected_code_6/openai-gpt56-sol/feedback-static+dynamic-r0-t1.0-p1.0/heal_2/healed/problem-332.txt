#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FREQUENCY_COUNT ((size_t)UCHAR_MAX + 1U)
#define BUFFER_SIZE 4096U

static int update_character_frequencies(
    const unsigned char *data,
    size_t length,
    size_t *frequencies,
    size_t frequency_count)
{
    if ((data == NULL && length != 0U) ||
        frequencies == NULL ||
        frequency_count < FREQUENCY_COUNT) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t index = (size_t)data[i];

        if (index >= frequency_count ||
            frequencies[index] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[index];
    }

    return 0;
}

int main(void)
{
    size_t *frequencies = calloc(FREQUENCY_COUNT, sizeof(*frequencies));
    unsigned char *buffer = malloc(BUFFER_SIZE);

    if (frequencies == NULL || buffer == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        free(buffer);
        free(frequencies);
        return EXIT_FAILURE;
    }

    for (;;) {
        size_t bytes_read = fread(buffer, sizeof(*buffer), BUFFER_SIZE, stdin);

        if (bytes_read != 0U &&
            update_character_frequencies(
                buffer, bytes_read, frequencies, FREQUENCY_COUNT) != 0) {
            fprintf(stderr, "Failed to count character frequencies.\n");
            free(buffer);
            free(frequencies);
            return EXIT_FAILURE;
        }

        if (bytes_read < BUFFER_SIZE) {
            if (ferror(stdin)) {
                fprintf(stderr, "Failed to read input.\n");
                free(buffer);
                free(frequencies);
                return EXIT_FAILURE;
            }
            break;
        }
    }

    for (size_t i = 0; i < FREQUENCY_COUNT; ++i) {
        if (frequencies[i] != 0U) {
            printf("0x%02zX: %zu\n", i, frequencies[i]);
        }
    }

    free(buffer);
    free(frequencies);
    return EXIT_SUCCESS;
}