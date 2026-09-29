#include <stdbool.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FIND_INVALID,
    FIND_NOT_FOUND,
    FIND_FOUND
} FindResult;

static FindResult find_first_repeated_character(
    const char *string,
    unsigned char *repeated_character
)
{
    bool seen[(size_t)UCHAR_MAX + 1U] = { false };
    const unsigned char *current;

    if (string == NULL || repeated_character == NULL) {
        return FIND_INVALID;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        if (seen[*current]) {
            *repeated_character = *current;
            return FIND_FOUND;
        }

        seen[*current] = true;
        ++current;
    }

    return FIND_NOT_FOUND;
}

int main(int argc, char * const argv[])
{
    unsigned char repeated_character;
    FindResult result;

    if (argc != 2) {
        const char *program_name =
            argc > 0 && argv[0] != NULL ? argv[0] : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    result = find_first_repeated_character(argv[1], &repeated_character);

    if (result == FIND_INVALID) {
        if (fputs("Invalid input.\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    if (result == FIND_NOT_FOUND) {
        if (puts("No repeated character found.") == EOF) {
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }

    if (printf("First repeated character: %c\n",
               (int)repeated_character) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}