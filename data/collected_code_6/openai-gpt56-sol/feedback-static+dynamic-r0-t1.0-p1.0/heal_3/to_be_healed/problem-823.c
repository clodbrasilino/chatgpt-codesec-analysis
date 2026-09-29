#include <regex.h>
#include <stdbool.h>
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

    result = snprintf(anchored_pattern, buffer_size, "^(%s)", pattern);
    if (result < 0 || (size_t)result >= buffer_size) {
        free(anchored_pattern);
        return REG_ESPACE;
    }

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

    if (regerror(error_code, NULL, error_message, required_size) == 0U) {
        fputs("Regex error\n", stderr);
    } else {
        fprintf(stderr, "Regex error: %s\n", error_message);
    }

    free(error_message);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    bool matches;
    int result;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <regex>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
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