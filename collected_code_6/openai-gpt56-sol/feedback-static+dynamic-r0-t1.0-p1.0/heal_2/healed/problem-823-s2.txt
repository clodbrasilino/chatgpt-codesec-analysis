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

    pattern_length = strlen(pattern);

    if (pattern_length > SIZE_MAX - 4U) {
        *error_code = REG_ESPACE;
        return false;
    }

    required_size = pattern_length + 4U;
    anchored_pattern = malloc(required_size);

    if (anchored_pattern == NULL) {
        *error_code = REG_ESPACE;
        return false;
    }

    result = snprintf(anchored_pattern, required_size, "^(%s)", pattern);

    if (result < 0 || (size_t)result >= required_size) {
        free(anchored_pattern);
        *error_code = REG_BADPAT;
        return false;
    }

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

int main(int argc, char *const argv[])
{
    int error_code;
    bool matches;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <regex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    matches = starts_with_regex(argv[1], argv[2], &error_code);

    if (error_code != 0) {
        char error_message[256];

        regerror(error_code, NULL, error_message, sizeof(error_message));
        fprintf(stderr, "Regex error: %s\n", error_message);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}