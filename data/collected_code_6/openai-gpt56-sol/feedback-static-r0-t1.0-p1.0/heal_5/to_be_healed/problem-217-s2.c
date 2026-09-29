#include <limits.h>
#include <stdbool.h>
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
    bool seen[UCHAR_MAX + 1] = { false };
    bool found = false;
    unsigned char repeated = 0;
    int character;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        unsigned char current = (unsigned char)character;

        if (!found && seen[current]) {
            repeated = current;
            found = true;
        }

        seen[current] = true;
    }

    if (ferror(stdin)) {
        return EXIT_FAILURE;
    }

    if (found) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}