#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_whitespace_and_underscore(char *str)
{
    if (str == NULL) {
        return -1;
    }

    for (unsigned char *cursor = (unsigned char *)str; *cursor != '\0'; ++cursor) {
        switch (*cursor) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        case '\f':
        case '\v':
            *cursor = '_';
            break;
        case '_':
            *cursor = ' ';
            break;
        default:
            break;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[0] == NULL || argv[1] == NULL) {
        const char *program = "program";

        if (argv != NULL && argc > 0 && argv[0] != NULL) {
            program = argv[0];
        }

        fprintf(stderr, "Usage: %s <string>\n", program);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t length = strlen(input);

    if (length > SIZE_MAX - 1) {
        fprintf(stderr, "Input is too long\n");
        return EXIT_FAILURE;
    }

    char *text = malloc(length + 1);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(text, input, length);
    text[length] = '\0';

    if (replace_whitespace_and_underscore(text) != 0) {
        fprintf(stderr, "Replacement failed\n");
        free(text);
        return EXIT_FAILURE;
    }

    if (puts(text) == EOF) {
        fprintf(stderr, "Output failed\n");
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}