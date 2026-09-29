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
    length = strlen(input);

    if (length == SIZE_MAX) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    string = malloc(length + 1);
    if (string == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    if (snprintf(string, length + 1, "%s", input) < 0) {
        fprintf(stderr, "String copy failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (replace_delimiters(string) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(string);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", string) < 0) {
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}