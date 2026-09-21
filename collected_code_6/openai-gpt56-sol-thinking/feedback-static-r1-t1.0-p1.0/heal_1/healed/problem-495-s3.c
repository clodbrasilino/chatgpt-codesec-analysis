#include <stdio.h>
#include <stdlib.h>

int remove_lowercase_substrings(char *string)
{
    char *source;
    char *destination;

    if (string == NULL) {
        fputs("Invalid string\n", stderr);
        return -1;
    }

    source = string;
    destination = string;

    while (*source != '\0') {
        unsigned char character = (unsigned char)*source++;

        if (character < (unsigned char)'a' || character > (unsigned char)'z') {
            *destination++ = (char)character;
        }
    }

    *destination = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
        ? argv[0]
        : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (remove_lowercase_substrings(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%s\n", argv[1]) < 0) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}