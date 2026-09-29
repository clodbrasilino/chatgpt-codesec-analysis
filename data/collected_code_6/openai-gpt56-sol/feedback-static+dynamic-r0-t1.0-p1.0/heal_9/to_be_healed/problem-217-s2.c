#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_first_repeated_character(const unsigned char *string,
                                   size_t length,
                                   unsigned char *repeated)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || repeated == NULL) {
        return false;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char character = string[i];

        if (seen[character]) {
            *repeated = character;
            return true;
        }

        seen[character] = true;
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[UCHAR_MAX + 1];
    unsigned char repeated;
    size_t length = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length < sizeof input) {
            input[length++] = (unsigned char)character;
        }
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (find_first_repeated_character(input, length, &repeated)) {
        if (printf("%c\n", (int)repeated) < 0) {
            return EXIT_FAILURE;
        }
    } else {
        if (puts("No repeated character") == EOF) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}