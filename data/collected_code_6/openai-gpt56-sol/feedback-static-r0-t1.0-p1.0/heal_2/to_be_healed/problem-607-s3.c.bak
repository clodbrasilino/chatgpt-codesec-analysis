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
    size_t i;
    size_t j = 0;

    if (literal == NULL) {
        return NULL;
    }

    length = strlen(literal);

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
                              size_t *start, size_t *end)
{
    regex_t regex;
    regmatch_t match;
    char *pattern;
    int result;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    pattern = escape_regex_literal(literal);
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

    if (result != 0 || match.rm_so < 0 || match.rm_eo < 0) {
        return -1;
    }

    *start = (size_t)match.rm_so;
    *end = (size_t)match.rm_eo;

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    size_t start;
    size_t end;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <literal>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = find_literal_regex(argv[1], argv[2], &start, &end);

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