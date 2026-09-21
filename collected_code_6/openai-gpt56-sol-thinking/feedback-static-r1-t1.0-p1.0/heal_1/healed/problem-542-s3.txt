#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int replace_with_colons(char *string, size_t length)
{
    size_t i;

    if (string == NULL) {
        return -1;
    }

    for (i = 0; i < length; ++i) {
        if (string[i] == ' ' || string[i] == ',' || string[i] == '.') {
            string[i] = ':';
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name;
    char *end;
    size_t length;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2 || argv[1] == NULL) {
        if (fprintf(stderr, "Usage: %s \"string\"\n", program_name) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    end = argv[1];
    while (*end != '\0') {
        ++end;
    }

    length = (size_t)(end - argv[1]);

    if (replace_with_colons(argv[1], length) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}