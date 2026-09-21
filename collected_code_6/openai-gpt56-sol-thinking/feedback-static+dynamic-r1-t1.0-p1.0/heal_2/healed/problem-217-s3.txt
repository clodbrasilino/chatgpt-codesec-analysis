#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum search_result {
    SEARCH_ERROR = -1,
    SEARCH_NOT_FOUND = 0,
    SEARCH_FOUND = 1
};

static enum search_result find_first_repeated_character(
    const char *string,
    unsigned char *result)
{
    unsigned char *seen;
    const size_t character_count = (size_t)UCHAR_MAX + 1U;

    if (string == NULL || result == NULL) {
        return SEARCH_ERROR;
    }

    seen = calloc(character_count, sizeof(*seen));
    if (seen == NULL) {
        return SEARCH_ERROR;
    }

    while (*string != '\0') {
        const unsigned char character = (unsigned char)*string;

        if (seen[character] != 0U) {
            *result = character;
            free(seen);
            return SEARCH_FOUND;
        }

        seen[character] = 1U;
        ++string;
    }

    free(seen);
    return SEARCH_NOT_FOUND;
}

int main(int argc, char *argv[])
{
    unsigned char repeated_character;
    enum search_result search_status;

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        const char *program_name =
            argv != NULL && argc > 0 && argv[0] != NULL
                ? argv[0]
                : "program";

        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
            return EXIT_FAILURE;
        }

        return EXIT_FAILURE;
    }

    search_status =
        find_first_repeated_character(argv[1], &repeated_character);

    if (search_status == SEARCH_ERROR) {
        if (fputs("Unable to search the string\n", stderr) == EOF) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (search_status == SEARCH_FOUND) {
        if (printf("%c\n", (int)repeated_character) < 0) {
            return EXIT_FAILURE;
        }
    } else if (puts("No repeated character found") == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}