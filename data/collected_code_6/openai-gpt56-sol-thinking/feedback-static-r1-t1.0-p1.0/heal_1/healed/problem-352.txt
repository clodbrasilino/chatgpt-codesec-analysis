#include <stdbool.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

bool all_characters_unique(const char *string)
{
    bool seen[(size_t)UCHAR_MAX + 1U] = {false};
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

int main(int argc, char *const argv[])
{
    const char *program_name;
    bool unique;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
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