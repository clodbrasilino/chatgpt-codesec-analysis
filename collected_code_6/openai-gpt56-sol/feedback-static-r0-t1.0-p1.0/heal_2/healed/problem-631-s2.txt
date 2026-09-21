#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_whitespace_and_underscores(char *string)
{
    if (string == NULL) {
        return -1;
    }

    for (unsigned char *p = (unsigned char *)string; *p != '\0'; ++p) {
        if (*p == '_') {
            *p = ' ';
        } else if (*p == ' ' || *p == '\t' || *p == '\n' ||
                   *p == '\r' || *p == '\f' || *p == '\v') {
            *p = '_';
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program =
            (argv != NULL && argv[0] != NULL) ? argv[0] : "program";
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    size_t length = strnlen(argv[1], SIZE_MAX);
    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large or not null-terminated\n");
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    snprintf(string, length + 1, "%s", argv[1]);

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