#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_unique(const unsigned char *str, size_t length)
{
    bool seen[256] = { false };

    if ((str == NULL && length != 0) || length > sizeof seen / sizeof seen[0]) {
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
    unsigned char input[256];
    size_t length = 0;
    bool overflow = false;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length < sizeof input) {
            input[length++] = (unsigned char)character;
        } else {
            overflow = true;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    const bool unique = !overflow && all_characters_unique(input, length);

    puts(unique ? "true" : "false");
    return EXIT_SUCCESS;
}