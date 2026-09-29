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
    enum { INPUT_SIZE = 4096 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char input[INPUT_SIZE];
    size_t length = 0;
    int character;
    bool truncated = false;
    unsigned char repeated;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = getchar()) != EOF && character != '\n') {
        if (length + 1 < sizeof input) {
            input[length++] = (unsigned char)character;
        } else {
            truncated = true;
        }
    }

    if (ferror(stdin) || truncated) {
        return EXIT_FAILURE;
    }

    input[length] = '\0';

    if (find_first_repeated_character(input, &repeated)) {
        if (putchar((int)repeated) == EOF || putchar('\n') == EOF) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}