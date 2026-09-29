#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int replace_delimiters(char *string)
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
    const char *input;
    char *string;
    size_t length;

    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    if (length > SIZE_MAX - 1) {
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
    memcpy(string, input, length);
    string[length] = '\0';

    if (replace_delimiters(string) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (puts(string) == EOF) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}