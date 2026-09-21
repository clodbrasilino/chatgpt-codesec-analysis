#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool find_first_repeated_character(const char *string,
                                          unsigned char *result)
{
    bool seen[(size_t)UCHAR_MAX + 1U] = { false };

    if (string == NULL || result == NULL) {
        return false;
    }

    while (*string != '\0') {
        unsigned char character = (unsigned char)*string;

        if (seen[character]) {
            *result = character;
            return true;
        }

        seen[character] = true;
        ++string;
    }

    return false;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    unsigned char repeated_character;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (find_first_repeated_character(argv[1], &repeated_character)) {
        if (printf("%c\n", (int)repeated_character) < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character found") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}