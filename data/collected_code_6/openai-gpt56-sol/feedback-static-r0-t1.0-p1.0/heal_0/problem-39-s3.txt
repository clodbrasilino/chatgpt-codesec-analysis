#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static bool can_rearrange_without_adjacent_duplicates(const char *str)
{
    size_t frequencies[256] = {0};
    size_t length;
    size_t max_frequency = 0;

    if (str == NULL) {
        return false;
    }

    length = strlen(str);

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = (unsigned char)str[i];

        ++frequencies[character];
        if (frequencies[character] > max_frequency) {
            max_frequency = frequencies[character];
        }
    }

    return max_frequency <= (length + 1U) / 2U;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return 1;
        }
        return 0;
    }

    size_t length = strlen(input);

    if (length > 0U && input[length - 1U] == '\n') {
        input[--length] = '\0';
        if (length > 0U && input[length - 1U] == '\r') {
            input[length - 1U] = '\0';
        }
    } else if (!feof(stdin)) {
        int character;

        do {
            character = getchar();
        } while (character != '\n' && character != EOF);

        if (character == EOF && ferror(stdin)) {
            return 1;
        }

        fputs("Input is too long.\n", stderr);
        return 1;
    }

    puts(can_rearrange_without_adjacent_duplicates(input) ? "true" : "false");

    return 0;
}