#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static int escape_regex_literal(const char *literal, char **escaped)
{
    static const char metacharacters[] = ".^$*+?()[]{}|\\";
    size_t length;
    size_t capacity;
    size_t position = 0;
    char *result;

    if (literal == NULL || escaped == NULL) {
        return -1;
    }

    length = strlen(literal);
    if (length > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    capacity = length * 2U + 1U;
    result = malloc(capacity);
    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if (strchr(metacharacters, literal[i]) != NULL) {
            result[position++] = '\\';
        }
        result[position++] = literal[i];
    }

    result[position] = '\0';
    *escaped = result;
    return 0;
}

static int find_literal_regex(const char *text, const char *literal,
                              size_t *start, size_t *end)
{
    regex_t regex;
    regmatch_t match;
    char *pattern = NULL;
    int status;

    if (text == NULL || literal == NULL || start == NULL || end == NULL) {
        return -1;
    }

    if (escape_regex_literal(literal, &pattern) != 0) {
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

    if (status != 0 || match.rm_so < 0 || match.rm_eo < 0) {
        return -1;
    }

    *start = (size_t)match.rm_so;
    *end = (size_t)match.rm_eo;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
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
        puts("Pattern not found");
        return EXIT_SUCCESS;
    }

    printf("Pattern found at [%zu, %zu)\n", start, end);
    return EXIT_SUCCESS;
}