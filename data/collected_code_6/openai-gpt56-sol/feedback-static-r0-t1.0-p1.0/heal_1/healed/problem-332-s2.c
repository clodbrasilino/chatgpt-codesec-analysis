#include <limits.h>
#include <stddef.h>
#include <stdio.h>

static void count_character_frequency(
    const unsigned char *data,
    size_t length,
    size_t frequency[UCHAR_MAX + 1])
{
    for (size_t i = 0; i < length; ++i) {
        ++frequency[data[i]];
    }
}

int main(void)
{
    size_t frequency[UCHAR_MAX + 1] = {0};
    unsigned char input[4096];

    for (;;) {
        size_t bytes_read = fread(input, 1, sizeof input, stdin);

        if (bytes_read > 0) {
            count_character_frequency(input, bytes_read, frequency);
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
        if (frequency[i] != 0) {
            printf("0x%02zX: %zu\n", i, frequency[i]);
        }
    }

    return 0;
}