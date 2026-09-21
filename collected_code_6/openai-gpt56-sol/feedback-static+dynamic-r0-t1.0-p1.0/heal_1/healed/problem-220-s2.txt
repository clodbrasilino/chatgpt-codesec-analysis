#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static size_t replace_delimiters(char *text, size_t max_replacements)
{
    size_t replacements = 0;

    if (text == NULL) {
        return 0;
    }

    for (char *p = text; *p != '\0' && replacements < max_replacements; ++p) {
        if (*p == ' ' || *p == ',' || *p == '.') {
            *p = ':';
            ++replacements;
        }
    }

    return replacements;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t max_replacements = 0;
    ssize_t length;

    if (scanf("%zu", &max_replacements) != 1) {
        fputs("Invalid replacement count.\n", stderr);
        return EXIT_FAILURE;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Missing input text.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length == 0 || line[length - 1] != '\n') {
        free(line);
        fputs("Invalid input format.\n", stderr);
        return EXIT_FAILURE;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        fputs("Failed to read input text.\n", stderr);
        return EXIT_FAILURE;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[--length] = '\0';
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    replace_delimiters(line, max_replacements);

    if (puts(line) == EOF) {
        free(line);
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}