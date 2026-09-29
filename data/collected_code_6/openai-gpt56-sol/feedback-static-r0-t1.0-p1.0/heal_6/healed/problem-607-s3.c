#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int bounded_string_length(const char *string, size_t limit,
                                 size_t *length)
{
    const char *terminator;

    if (string == NULL || length == NULL) {
        return -1;
    }

    terminator = memchr(string, '\0', limit);
    if (terminator == NULL) {
        return -1;
    }

    *length = (size_t)(terminator - string);
    return 0;
}

static char *escape_regex_literal(const char *literal, size_t length)
{
    static const char metacharacters[] = ".^$*+?()[]{}|\\";
    size_t escaped_length = 0;
    size_t i;
    size_t j = 0;
    char *escaped;

    if (literal == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        size_t increment =
            strchr(metacharacters, (unsigned char)literal[i]) != NULL ? 2U : 1U;

        if (escaped_length > SIZE_MAX - increment) {
            return NULL;
        }

        escaped_length += increment;
    }

    if (escaped_length == SIZE_MAX) {
        return NULL;
    }

    escaped = malloc(escaped_length + 1U);
    if (escaped == NULL) {
        return NULL;
    }

    for (i = 0; i < length; ++i) {
        if (strchr(metacharacters, (unsigned char)literal[i]) != NULL) {
            escaped[j++] = '\\';
        }

        escaped[j++] = literal[i];
    }

    escaped[j] = '\0';
    return escaped;
}

static int find_literal_regex(const char *text, const char *literal,
                              size_t literal_length, size_t *start,
                              size_t *end)
{
    regex_t regex;
    regmatch_t match;
    char *pattern;
    int result;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    pattern = escape_regex_literal(literal, literal_length);
    if (pattern == NULL) {
        return -1;
    }

    result = regcomp(&regex, pattern, 0);
    free(pattern);

    if (result != 0) {
        return -1;
    }

    result = regexec(&regex, text, 1, &match, 0);
    regfree(&regex);

    if (result == REG_NOMATCH) {
        return 0;
    }

    if (result != 0 || match.rm_so < 0 || match.rm_eo < match.rm_so) {
        return -1;
    }

    *start = (size_t)match.rm_so;
    *end = (size_t)match.rm_eo;
    return 1;
}

int main(int argc, char *argv[])
{
    const size_t maximum_argument_length = 1024U * 1024U;
    const char *text;
    const char *literal;
    size_t text_length;
    size_t literal_length;
    size_t start;
    size_t end;
    int result;

    if (argc != 3 || argv == NULL) {
        const char *program =
            argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

        fprintf(stderr, "Usage: %s <string> <literal>\n", program);
        return EXIT_FAILURE;
    }

    text = argv[1];
    literal = argv[2];

    if (text == NULL || literal == NULL ||
        bounded_string_length(text, maximum_argument_length, &text_length) != 0 ||
        bounded_string_length(literal, maximum_argument_length,
                              &literal_length) != 0) {
        fputs("Invalid or excessively long argument\n", stderr);
        return EXIT_FAILURE;
    }

    result = find_literal_regex(text, literal, literal_length, &start, &end);

    if (result < 0) {
        fputs("Search failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (result == 0) {
        puts("Not found");
        return EXIT_SUCCESS;
    }

    printf("Found at byte range [%zu, %zu)\n", start, end);
    return EXIT_SUCCESS;
}