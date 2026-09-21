#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define INPUT_CAPACITY 4096U

static bool can_rearrange_without_equal_adjacent(const char *str, size_t length)
{
    size_t frequencies[256] = {0};
    size_t max_frequency = 0;

    if (str == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)str[i];

        ++frequencies[character];
        if (frequencies[character] > max_frequency) {
            max_frequency = frequencies[character];
        }
    }

    return max_frequency <= (length / 2U) + (length % 2U);
}

int main(void)
{
    char input[INPUT_CAPACITY];
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != '\n' && character != EOF) {
        if (length + 1U >= sizeof(input)) {
            do {
                character = fgetc(stdin);
            } while (character != '\n' && character != EOF);

            if (ferror(stdin)) {
                return 1;
            }

            if (fputs("Input is too long.\n", stderr) == EOF) {
                return 1;
            }

            return 1;
        }

        input[length++] = (char)character;
    }

    if (ferror(stdin)) {
        return 1;
    }

    if (character == EOF && length == 0U) {
        return 0;
    }

    if (length > 0U && input[length - 1U] == '\r') {
        --length;
    }

    input[length] = '\0';

    if (puts(can_rearrange_without_equal_adjacent(input, length)
                 ? "true"
                 : "false") == EOF) {
        return 1;
    }

    return 0;
}