#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long minimum_operations(long long first, long long second)
{
    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    return (unsigned long long)second - (unsigned long long)first;
}

static int parse_long_long(const char **text, long long *value)
{
    char *end;
    long long parsed;

    while (isspace((unsigned char)**text)) {
        ++*text;
    }

    if (**text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoll(*text, &end, 10);

    if (errno == ERANGE || end == *text) {
        return 0;
    }

    *text = end;
    *value = parsed;
    return 1;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    const char *cursor;
    long long first;
    long long second;
    int result = EXIT_FAILURE;

    if (getline(&line, &capacity, stdin) < 0) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    cursor = line;

    if (!parse_long_long(&cursor, &first) ||
        !parse_long_long(&cursor, &second)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(line);
    return result;
}