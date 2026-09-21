#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int replace_whitespace_and_underscores(char *string)
{
    unsigned char *p;

    if (string == NULL) {
        return -1;
    }

    for (p = (unsigned char *)string; *p != '\0'; ++p) {
        if (*p == '_') {
            *p = ' ';
        } else if (*p == ' ' || (*p >= '\t' && *p <= '\r')) {
            *p = '_';
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    char *string;
    size_t length;

    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program =
            argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    length = strnlen(argv[1], SIZE_MAX);
    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (length > 0) {
        memcpy(string, argv[1], length);
    }
    string[length] = '\0';

    if (replace_whitespace_and_underscores(string) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        fprintf(stderr, "Output failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}