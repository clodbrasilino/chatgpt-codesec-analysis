#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define FREQUENCY_COUNT ((size_t)UCHAR_MAX + 1U)
#define INPUT_BUFFER_SIZE 4096U

static int count_character_frequency(
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

    for (size_t i = 0; i < frequency_count; ++i) {
        frequencies[i] = 0U;
    }

    for (size_t i = 0; i < length; ++i) {
        const size_t index = (size_t)data[i];

        if (index >= frequency_count || frequencies[index] == SIZE_MAX) {
            return -1;
        }

        ++frequencies[index];
    }

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_BUFFER_SIZE];
    size_t frequencies[FREQUENCY_COUNT];

    const size_t length = fread(input, sizeof input[0], INPUT_BUFFER_SIZE, stdin);

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_character_frequency(
            input, length, frequencies, FREQUENCY_COUNT) != 0) {
        fputs("Failed to count character frequencies.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < FREQUENCY_COUNT; ++i) {
        if (frequencies[i] != 0U) {
            if (printf("0x%02zX: %zu\n", i, frequencies[i]) < 0) {
                fputs("Failed to write output.\n", stderr);
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}