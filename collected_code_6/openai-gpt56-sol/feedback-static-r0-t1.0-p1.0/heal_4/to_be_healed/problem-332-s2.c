#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define FREQUENCY_SIZE ((size_t)UCHAR_MAX + 1U)
#define INPUT_SIZE 4096U

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t *frequency,
    size_t frequency_size)
{
    if (data == NULL || frequency == NULL || frequency_size < FREQUENCY_SIZE) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        size_t value = data[i];

        if (value >= frequency_size || frequency[value] == SIZE_MAX) {
            return -1;
        }

        ++frequency[value];
    }

    return 0;
}

int main(void)
{
    size_t frequency[FREQUENCY_SIZE] = {0};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_SIZE];

    for (;;) {
        size_t bytes_read = fread(input, 1U, sizeof input, stdin);

        if (bytes_read > 0U &&
            count_character_frequency(
                input, bytes_read, frequency, FREQUENCY_SIZE) != 0) {
            fputs("Character count overflow.\n", stderr);
            return 1;
        }

        if (bytes_read < sizeof input) {
            if (ferror(stdin)) {
                fputs("Failed to read input.\n", stderr);
                return 1;
            }

            break;
        }
    }

    for (size_t i = 0; i < FREQUENCY_SIZE; ++i) {
        if (frequency[i] > 0U) {
            printf("0x%02zX: %zu\n", i, frequency[i]);
        }
    }

    return 0;
}