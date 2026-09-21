#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum { BYTE_VALUE_COUNT = 256 };

static bool all_characters_unique(const unsigned char *data, size_t length)
{
    bool seen[BYTE_VALUE_COUNT] = { false };

    if (data == NULL && length != 0) {
        return false;
    }

    if (length > BYTE_VALUE_COUNT) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        if (seen[data[i]]) {
            return false;
        }

        seen[data[i]] = true;
    }

    return true;
}

int main(void)
{
    unsigned char input[BYTE_VALUE_COUNT];
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

    puts(!overflow && all_characters_unique(input, length) ? "true" : "false");

    return EXIT_SUCCESS;
}