#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool all_characters_unique(const unsigned char *str, size_t length)
{
    bool seen[256] = { false };

    if (str == NULL && length != 0) {
        return false;
    }

    if (length > sizeof seen / sizeof seen[0]) {
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
    bool seen[256] = { false };
    bool unique = true;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length >= sizeof seen / sizeof seen[0]) {
            unique = false;
            continue;
        }

        unsigned char value = (unsigned char)character;

        if (seen[value]) {
            unique = false;
        }

        seen[value] = true;
        ++length;
    }

    if (ferror(stdin)) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (unique) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        unsigned char input[256];

        for (size_t i = 0, j = 0; i < sizeof seen / sizeof seen[0]; ++i) {
            if (seen[i]) {
                input[j++] = (unsigned char)i;
            }
        }

        unique = all_characters_unique(input, length);
    }

    puts(unique ? "true" : "false");
    return EXIT_SUCCESS;
}