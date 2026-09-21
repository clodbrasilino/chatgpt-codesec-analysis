#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FREQUENCY_SIZE ((size_t)UCHAR_MAX + 1U)
#define INPUT_SIZE ((size_t)4096U)

static int count_character_frequency(
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const unsigned char *data,
    size_t length,
    size_t frequency[FREQUENCY_SIZE])
{
    if (frequency == NULL || (data == NULL && length != 0U)) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        const size_t index = (size_t)data[i];

        if (frequency[index] == SIZE_MAX) {
            return -1;
        }

        ++frequency[index];
    }

    return 0;
}

int main(void)
{
    size_t frequency[FREQUENCY_SIZE] = {0U};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_SIZE];

    for (;;) {
        size_t bytes_read = fread(input, 1U, sizeof input, stdin);

        if (bytes_read != 0U &&
            count_character_frequency(input, bytes_read, frequency) != 0) {
            fputs("Character count overflow.\n", stderr);
            return 1;
        }

        if (bytes_read < sizeof input) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            if (feof(stdin)) {
                break;
            }
        }
    }

    for (size_t i = 0U; i < FREQUENCY_SIZE; ++i) {
        if (frequency[i] != 0U &&
            printf("0x%02zX: %zu\n", i, frequency[i]) < 0) {
            fputs("Failed to write output.\n", stderr);
            return 1;
        }
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return 1;
    }

    return 0;
}