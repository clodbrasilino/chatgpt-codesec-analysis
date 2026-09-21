#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool starts_with_regex(const char *string, const char *pattern,
                              int *error_code)
{
    regex_t regex;
    regmatch_t match;
    char *anchored_pattern;
    size_t pattern_length;
    size_t required_size;
    int result;

    if (error_code == NULL) {
        return false;
    }

    *error_code = 0;

    if (string == NULL || pattern == NULL) {
        *error_code = REG_BADPAT;
        return false;
    }

    pattern_length = strnlen(pattern, SIZE_MAX - 4U);

    if (pattern_length == SIZE_MAX - 4U) {
        *error_code = REG_ESPACE;
        return false;
    }

    required_size = pattern_length + 4U;
    anchored_pattern = malloc(required_size);

    if (anchored_pattern == NULL) {
        *error_code = REG_ESPACE;
        return false;
    }

    anchored_pattern[0] = '^';
    anchored_pattern[1] = '(';
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(anchored_pattern + 2U, pattern, pattern_length);
    anchored_pattern[pattern_length + 2U] = ')';
    anchored_pattern[pattern_length + 3U] = '\0';

    result = regcomp(&regex, anchored_pattern, REG_EXTENDED);
    free(anchored_pattern);

    if (result != 0) {
        *error_code = result;
        return false;
    }

    result = regexec(&regex, string, 1U, &match, 0);
    regfree(&regex);

    if (result == 0) {
        return match.rm_so == 0;
    }

    if (result != REG_NOMATCH) {
        *error_code = result;
    }

    return false;
}

static void print_regex_error(int error_code)
{
    size_t required_size;
    char *error_message;

    required_size = regerror(error_code, NULL, NULL, 0);

    if (required_size == 0U) {
        fputs("Regex error\n", stderr);
        return;
    }

    error_message = malloc(required_size);

    if (error_message == NULL) {
        fputs("Regex error: unable to allocate error message\n", stderr);
        return;
    }

    regerror(error_code, NULL, error_message, required_size);
    fprintf(stderr, "Regex error: %s\n", error_message);
    free(error_message);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    int error_code;
    bool matches;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <regex>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    matches = starts_with_regex(argv[1], argv[2], &error_code);

    if (error_code != 0) {
        print_regex_error(error_code);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}