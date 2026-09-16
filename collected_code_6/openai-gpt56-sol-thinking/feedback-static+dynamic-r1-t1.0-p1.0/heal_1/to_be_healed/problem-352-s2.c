#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

bool all_characters_unique(const char *string)
{
    bool seen[UCHAR_MAX + 1] = { false };

    if (string == NULL) {
        return false;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (seen[character]) {
            return false;
        }

        seen[character] = true;
        ++string;
    }

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", all_characters_unique(argv[1]) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}