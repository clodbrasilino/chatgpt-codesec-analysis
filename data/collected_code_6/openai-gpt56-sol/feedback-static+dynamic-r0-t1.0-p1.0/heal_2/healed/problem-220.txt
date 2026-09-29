#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdint.h>
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

static int parse_size(const char *str, size_t *value)
{
    char *end;
    uintmax_t parsed;

    if (str == NULL || value == NULL || *str == '\0' || *str == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(str, &end, 10);

    if (errno == ERANGE || end == str || parsed > SIZE_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return 0;
    }

    *value = (size_t)parsed;
    return 1;
}

int main(void)
{
    char *count_line = NULL;
    char *line = NULL;
    size_t count_capacity = 0;
    size_t line_capacity = 0;
    size_t max_replacements;
    int status = EXIT_FAILURE;

    if (getline(&count_line, &count_capacity, stdin) < 0 ||
        !parse_size(count_line, &max_replacements)) {
        fprintf(stderr, "Failed to read the maximum replacement count.\n");
        goto cleanup;
    }

    if (getline(&line, &line_capacity, stdin) < 0) {
        fprintf(stderr, "Failed to read the input string.\n");
        goto cleanup;
    }

    replace_delimiters(line, max_replacements);

    if (fputs(line, stdout) == EOF) {
        fprintf(stderr, "Failed to write the result.\n");
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(count_line);
    free(line);
    return status;
}