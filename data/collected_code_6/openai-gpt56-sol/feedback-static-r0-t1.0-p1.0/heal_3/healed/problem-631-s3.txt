#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int replace_whitespace_and_underscore(char *str)
{
    if (str == NULL) {
        return -1;
    }

    for (unsigned char *p = (unsigned char *)str; *p != '\0'; ++p) {
        switch (*p) {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
        case '\f':
        case '\v':
            *p = '_';
            break;
        case '_':
            *p = ' ';
            break;
        default:
            break;
        }
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: program <string>\n");
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    char *text = strdup(input);

    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

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