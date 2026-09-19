#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int all_characters_are_unique(const char *string)
{
    unsigned char seen[UCHAR_MAX + 1U] = {0};
    size_t index;

    if (string == NULL) {
        return -1;
    }

    for (index = 0; string[index] != '\0'; ++index) {
        unsigned char character = (unsigned char)string[index];

        if (seen[character] != 0U) {
            return 0;
        }

        seen[character] = 1U;
    }

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int result;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    result = all_characters_are_unique(argv[1]);
    if (result < 0) {
        if (fputs("Unable to process the string.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(result != 0 ? "true" : "false") == EOF) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}