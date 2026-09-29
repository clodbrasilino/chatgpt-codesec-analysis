#include <stdio.h>
#include <stdlib.h>

int replace_with_colons(char *string)
{
    char *cursor;

    if (string == NULL) {
        return -1;
    }

    for (cursor = string; *cursor != '\0'; ++cursor) {
        if (*cursor == ' ' || *cursor == ',' || *cursor == '.') {
            *cursor = ':';
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name =
        (argc > 0 && argv != NULL && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s \"string\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (replace_with_colons(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}