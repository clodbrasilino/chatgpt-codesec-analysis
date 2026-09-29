#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

bool all_characters_unique(const char *string)
{
    bool seen[UCHAR_MAX + 1] = {false};
    const unsigned char *current;

    if (string == NULL) {
        return false;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (seen[*current]) {
            return false;
        }

        seen[*current] = true;
        ++current;
    }

    return true;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    bool unique;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    unique = all_characters_unique(argv[1]);

    if (printf("%s\n", unique ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}