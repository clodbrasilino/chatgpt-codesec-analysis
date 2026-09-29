#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

static int count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t frequency[static UCHAR_MAX + 1U])
{
    if (data == NULL || frequency == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned int value = data[i];

        if (frequency[value] == SIZE_MAX) {
            return -1;
        }

        ++frequency[value];
    }

    return 0;
}

int main(void)
{
    size_t frequency[UCHAR_MAX + 1U] = {0};
    unsigned char input[4096];

    for (;;) {
        size_t bytes_read = fread(input, sizeof input[0], sizeof input, stdin);

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
            break;
        }
    }

    for (size_t i = 0; i < UCHAR_MAX + 1U; ++i) {
        if (frequency[i] != 0U) {
            printf("0x%02zX: %zu\n", i, frequency[i]);
        }
    }

    return 0;
}