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
    unsigned char input[4096];
    size_t frequency[UCHAR_MAX + 1] = {0};
    size_t bytes_read;

    while ((bytes_read = fread(input, 1, sizeof input, stdin)) != 0) {
        count_character_frequency(input, bytes_read, frequency);
    }

    if (ferror(stdin)) {
        fprintf(stderr, "Failed to read input.\n");
        return 1;
    }

    for (size_t i = 0; i <= UCHAR_MAX; ++i) {
        if (frequency[i] != 0) {
            printf("0x%02zX: %zu\n", i, frequency[i]);
        }
    }

    return 0;
}