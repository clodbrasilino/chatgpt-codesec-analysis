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
        const unsigned char character = (unsigned char)*string;

        if (seen[character]) {
            return false;
        }

        seen[character] = true;
        ++string;
    }

    return true;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    if (argc != 2) {
        const char *program_name = argc > 0 && argv[0] != NULL
            ? argv[0]
            : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (printf("%s\n",
               all_characters_unique(argv[1]) ? "true" : "false") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}