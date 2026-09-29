#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t replace_delimiters(char *string, size_t maximum)
{
    size_t replaced = 0;

    if (string == NULL) {
        return 0;
    }

    while (*string != '\0' && replaced < maximum) {
        if (*string == ' ' || *string == ',' || *string == '.') {
            *string = ':';
            ++replaced;
        }
        ++string;
    }

    return replaced;
}

static int read_maximum(size_t *maximum)
{
    char *line = NULL;
    char *end = NULL;
    size_t capacity = 0;
    uintmax_t value;

    if (maximum == NULL) {
        return 0;
    }

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    value = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || value > SIZE_MAX) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        free(line);
        return 0;
    }

    *maximum = (size_t)value;
    free(line);
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    size_t maximum;

    if (printf("Maximum replacements: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_maximum(&maximum)) {
        return EXIT_FAILURE;
    }

    if (printf("Text: ") < 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    replace_delimiters(line, maximum);

    if (fputs(line, stdout) == EOF) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}