#include <stdbool.h>
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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[256];
    size_t length = 0;
    int character;
    bool too_long = false;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length < sizeof input) {
            input[length++] = (unsigned char)character;
        } else {
            too_long = true;
        }
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    puts(!too_long && all_characters_unique(input, length) ? "true" : "false");
    return EXIT_SUCCESS;
}