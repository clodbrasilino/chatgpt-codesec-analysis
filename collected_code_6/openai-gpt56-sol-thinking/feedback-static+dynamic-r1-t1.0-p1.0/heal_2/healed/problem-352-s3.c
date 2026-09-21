#include <stdio.h>
#include <stdlib.h>

int all_characters_are_unique(const char *string)
{
    const unsigned char *current;

    if (string == NULL) {
        return -1;
    }

    current = (const unsigned char *)string;

    while (*current != '\0') {
        const unsigned char *candidate = current + 1;

        while (*candidate != '\0') {
            if (*candidate == *current) {
                return 0;
            }
            ++candidate;
        }

        ++current;
    }

    return 1;
}

int main(int argc, char **argv)
{
    const char *program_name;
    int result;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", program_name) < 0) {
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