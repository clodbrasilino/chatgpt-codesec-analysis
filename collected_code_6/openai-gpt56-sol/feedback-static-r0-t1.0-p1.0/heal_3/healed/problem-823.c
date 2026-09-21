#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int starts_with_regex(const char *string, const char *pattern,
                             bool *matches)
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

    if (pattern_length != 0U) {
        memcpy(&anchored_pattern[2], pattern, pattern_length);
    }

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
    } else if (result == REG_NOMATCH) {
        result = 0;
    }

    regfree(&regex);
    return result;
}

int main(int argc, char *argv[])
{
    bool matches;
    int result;

    if (argc != 3) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "program";

        fprintf(stderr, "Usage: %s <string> <regex>\n", program_name);
        return EXIT_FAILURE;
    }

    result = starts_with_regex(argv[1], argv[2], &matches);
    if (result != 0) {
        char *error_message;
        size_t message_size = regerror(result, NULL, NULL, 0U);

        if (message_size == 0U) {
            fputs("Regex error\n", stderr);
            return EXIT_FAILURE;
        }

        error_message = malloc(message_size);
        if (error_message == NULL) {
            fputs("Regex error: unable to allocate error message\n", stderr);
            return EXIT_FAILURE;
        }

        if (regerror(result, NULL, error_message, message_size) == 0U) {
            fputs("Regex error\n", stderr);
        } else {
            fprintf(stderr, "Regex error: %s\n", error_message);
        }

        free(error_message);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}