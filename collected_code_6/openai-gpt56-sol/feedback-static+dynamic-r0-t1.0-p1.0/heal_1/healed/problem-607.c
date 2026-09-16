#include <regex.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *escape_regex_literal(const char *literal)
{
    static const char metacharacters[] = ".^$*+?()[]{}|\\";
    size_t length;
    size_t escaped_length = 0;
    char *escaped;
    char *output;

    if (literal == NULL) {
        return NULL;
    }

    length = strlen(literal);

    for (size_t i = 0; i < length; ++i) {
        size_t increment = strchr(metacharacters, literal[i]) != NULL ? 2 : 1;

        if (escaped_length > SIZE_MAX - increment) {
            return NULL;
        }

        escaped_length += increment;
    }

    if (escaped_length == SIZE_MAX) {
        return NULL;
    }

    escaped = malloc(escaped_length + 1);
    if (escaped == NULL) {
        return NULL;
    }

    output = escaped;

    for (size_t i = 0; i < length; ++i) {
        if (strchr(metacharacters, literal[i]) != NULL) {
            *output++ = '\\';
        }

        *output++ = literal[i];
    }

    *output = '\0';
    return escaped;
}

static int find_literal(const char *text, const char *literal,
                        size_t *start, size_t *length)
{
    regex_t regex;
    regmatch_t match;
    char *pattern;
    int status;

    if (text == NULL || literal == NULL || start == NULL || length == NULL) {
        return -1;
    }

    pattern = escape_regex_literal(literal);
    if (pattern == NULL) {
        return -1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);

    if (status != 0) {
        return -1;
    }

    status = regexec(&regex, text, 1, &match, 0);
    regfree(&regex);

    if (status == REG_NOMATCH) {
        return 0;
    }

    if (status != 0 || match.rm_so < 0 || match.rm_eo < match.rm_so) {
        return -1;
    }

    *start = (size_t)match.rm_so;
    *length = (size_t)(match.rm_eo - match.rm_so);

    return 1;
}

int main(int argc, char * const argv[])
{
    size_t start;
    size_t length;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <literal>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = find_literal(argv[1], argv[2], &start, &length);

    if (result < 0) {
        fputs("Search failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("Not found");
        return EXIT_SUCCESS;
    }

    printf("Found at index %zu, length %zu\n", start, length);
    return EXIT_SUCCESS;
}