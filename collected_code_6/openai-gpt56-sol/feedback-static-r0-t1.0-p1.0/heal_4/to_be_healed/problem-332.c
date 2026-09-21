#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FREQUENCY_COUNT ((size_t)UCHAR_MAX + 1U)
#define INPUT_BUFFER_SIZE 4096U

static int count_character_frequency(
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const unsigned char *data,
    size_t length,
    size_t frequencies[FREQUENCY_COUNT])
{
    if ((data == NULL && length != 0U) || frequencies == NULL) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        const size_t index = (size_t)data[i];

        if (frequencies[index] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[index];
    }

    return 0;
}

int main(void)
{
    unsigned char *input = malloc(INPUT_BUFFER_SIZE * sizeof *input);
    size_t *frequencies = calloc(FREQUENCY_COUNT, sizeof *frequencies);

    if (input == NULL || frequencies == NULL) {
        fputs("Failed to allocate memory.\n", stderr);
        free(frequencies);
        free(input);
        return EXIT_FAILURE;
    }

    for (;;) {
        const size_t length =
            fread(input, sizeof *input, INPUT_BUFFER_SIZE, stdin);

        if (count_character_frequency(input, length, frequencies) != 0) {
            fputs("Failed to count character frequencies.\n", stderr);
            free(frequencies);
            free(input);
            return EXIT_FAILURE;
        }

        if (length < INPUT_BUFFER_SIZE) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                free(frequencies);
                free(input);
                return EXIT_FAILURE;
            }

            if (feof(stdin)) {
                break;
            }
        }
    }

    for (size_t i = 0U; i < FREQUENCY_COUNT; ++i) {
        if (frequencies[i] != 0U &&
            printf("0x%02zX: %zu\n", i, frequencies[i]) < 0) {
            fputs("Failed to write output.\n", stderr);
            free(frequencies);
            free(input);
            return EXIT_FAILURE;
        }
    }

    free(frequencies);
    free(input);
    return EXIT_SUCCESS;
}