#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

size_t replace_delimiters(char *str, size_t max_replacements)
{
    size_t replacements = 0;

    if (str == NULL) {
        return 0;
    }

    while (*str != '\0' && replacements < max_replacements) {
        if (*str == ' ' || *str == ',' || *str == '.') {
            *str = ':';
            ++replacements;
        }
        ++str;
    }

    return replacements;
}

static int discard_line(FILE *stream)
{
    char *buffer = NULL;
    size_t capacity = 0;
    ssize_t length;

    errno = 0;
    length = getline(&buffer, &capacity, stream);
    free(buffer);

    if (length < 0) {
        return ferror(stream) ? -1 : 0;
    }

    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t max_replacements;
    ssize_t length;
    int status;

    if (scanf("%zu", &max_replacements) != 1) {
        fprintf(stderr, "Failed to read the maximum replacement count.\n");
        return EXIT_FAILURE;
    }

    status = discard_line(stdin);
    if (status < 0) {
        fprintf(stderr, "Failed while reading input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        if (ferror(stdin)) {
            fprintf(stderr, "Failed while reading the input string.\n");
        } else {
            fprintf(stderr, "No input string was provided.\n");
        }
        free(line);
        return EXIT_FAILURE;
    }

    replace_delimiters(line, max_replacements);

    if (fputs(line, stdout) == EOF) {
        fprintf(stderr, "Failed to write the result.\n");
        free(line);
        return EXIT_FAILURE;
    }

    free(line);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to flush the output.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}