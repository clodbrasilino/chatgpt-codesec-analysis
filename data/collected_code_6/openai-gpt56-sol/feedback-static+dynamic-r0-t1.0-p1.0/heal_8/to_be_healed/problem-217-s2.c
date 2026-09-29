#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool find_first_repeated_character(const unsigned char *string,
                                   unsigned char *repeated)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL || repeated == NULL) {
        return false;
    }

    while (*string != '\0') {
        unsigned char character = *string++;

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
    unsigned char input[UCHAR_MAX + 2];
    unsigned char repeated;
    size_t length = 0;
    int character = EOF;

    while (length < sizeof(input) - 1) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        character = fgetc(stdin);

        if (character == EOF || character == '\n') {
            break;
        }

        input[length++] = (unsigned char)character;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (length == sizeof(input) - 1 &&
        character != EOF &&
        character != '\n') {
        do {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            character = fgetc(stdin);
        } while (character != EOF && character != '\n');

        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
    }

    input[length] = '\0';

    if (find_first_repeated_character(input, &repeated)) {
        printf("%c\n", (int)repeated);
    } else {
        puts("No repeated character");
    }

    return EXIT_SUCCESS;
}