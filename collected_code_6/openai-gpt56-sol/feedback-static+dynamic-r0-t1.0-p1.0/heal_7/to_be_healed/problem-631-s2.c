#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    const char *program;
    char *string;
    size_t length;

    program = (argv != NULL && argv[0] != NULL) ? argv[0] : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(argv[1]);

    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(string, argv[1], length);
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