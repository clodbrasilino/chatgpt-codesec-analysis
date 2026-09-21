#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_unique(const unsigned char *str, size_t length)
{
    bool seen[256] = { false };

    if (str == NULL && length != 0) {
        return false;
    }

    if (length > 256) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (seen[str[i]]) {
            return false;
        }

        seen[str[i]] = true;
    }

    return true;
}

int main(void)
{
    unsigned char input[257];
    size_t length = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length < sizeof(input)) {
            input[length++] = (unsigned char)character;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(all_characters_unique(input, length) ? "true" : "false");
    return EXIT_SUCCESS;
}