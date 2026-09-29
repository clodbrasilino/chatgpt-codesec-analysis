#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int starts_with_regex(const char *string,
                             const char *pattern,
                             bool *matches)
{
    regex_t regex;
    char *anchored_pattern;
    size_t pattern_length;
    size_t buffer_size;
    int result;

    if (string == NULL || pattern == NULL || matches == NULL) {
        return REG_BADPAT;
    }

    *matches = false;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    pattern_length = strlen(pattern);

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

    result = regexec(&regex, string, 0U, NULL, 0);
    if (result == 0) {
        *matches = true;
    } else if (result == REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

static void print_regex_error(int error_code)
{
    regex_t regex;
    size_t required_size;
    char *error_message;

    memset(&regex, 0, sizeof(regex));
    required_size = regerror(error_code, &regex, NULL, 0U);

    if (required_size == 0U) {
        fputs("Regex error\n", stderr);
        return;
    }

    error_message = malloc(required_size);
    if (error_message == NULL) {
        fputs("Regex error: unable to allocate error buffer\n", stderr);
        return;
    }

    if (regerror(error_code, &regex, error_message, required_size) == 0U) {
        fputs("Regex error\n", stderr);
    } else {
        fprintf(stderr, "Regex error: %s\n", error_message);
    }

    free(error_message);
}

int main(int argc, char *argv[])
{
    const char *program_name;
    bool matches;
    int result;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string> <regex>\n", program_name);
        return EXIT_FAILURE;
    }

    result = starts_with_regex(argv[1], argv[2], &matches);
    if (result != 0) {
        print_regex_error(result);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}