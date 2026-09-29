#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int starts_with_regex(const char *string, const char *pattern, bool *matches)
{
    regex_t regex;
    regmatch_t match;
    char *anchored_pattern;
    size_t pattern_length;
    size_t buffer_size;
    int result;

    if (string == NULL || pattern == NULL || matches == NULL) {
        return REG_BADPAT;
    }

    *matches = false;
    pattern_length = strnlen(pattern, SIZE_MAX);

    if (pattern_length > SIZE_MAX - 4U) {
        return REG_ESPACE;
    }

    buffer_size = pattern_length + 4U;
    anchored_pattern = malloc(buffer_size);
    if (anchored_pattern == NULL) {
        return REG_ESPACE;
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
        return result;
    }

    result = regexec(&regex, string, 1U, &match, 0);
    if (result == 0) {
        *matches = match.rm_so == 0;
    } else if (result != REG_NOMATCH) {
        regfree(&regex);
        return result;
    }

    regfree(&regex);
    return 0;
}

static void print_regex_error(int error_code)
{
    size_t required_size;
    char *error_message;

    required_size = regerror(error_code, NULL, NULL, 0U);
    if (required_size == 0U) {
        fputs("Regex error\n", stderr);
        return;
    }

    error_message = malloc(required_size);
    if (error_message == NULL) {
        fputs("Regex error: unable to allocate error buffer\n", stderr);
        return;
    }

    regerror(error_code, NULL, error_message, required_size);
    fprintf(stderr, "Regex error: %s\n", error_message);
    free(error_message);
}

int main(int argc, char *argv[])
{
    const char *string;
    const char *pattern;
    bool matches;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <regex>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    string = argv[1];
    pattern = argv[2];

    result = starts_with_regex(string, pattern, &matches);
    if (result != 0) {
        print_regex_error(result);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}