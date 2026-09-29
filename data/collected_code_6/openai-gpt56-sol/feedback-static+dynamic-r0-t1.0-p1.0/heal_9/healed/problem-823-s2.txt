#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool starts_with_regex(const char *string, const char *pattern,
                              int *error_code)
{
    regex_t regex;
    regmatch_t match;
    int result;

    if (error_code == NULL) {
        return false;
    }

    *error_code = 0;

    if (string == NULL || pattern == NULL) {
        *error_code = REG_BADPAT;
        return false;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        *error_code = result;
        return false;
    }

    result = regexec(&regex, string, 1, &match, 0);
    regfree(&regex);

    if (result == 0) {
        return match.rm_so == 0;
    }

    if (result != REG_NOMATCH) {
        *error_code = result;
    }

    return false;
}

int main(int argc, const char *const argv[])
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
        size_t message_size;
        char *error_message;

        message_size = regerror(error_code, NULL, NULL, 0);
        if (message_size == 0U) {
            fputs("Regex error\n", stderr);
            return EXIT_FAILURE;
        }

        error_message = malloc(message_size);
        if (error_message == NULL) {
            fputs("Regex error: unable to allocate error message\n", stderr);
            return EXIT_FAILURE;
        }

        if (regerror(error_code, NULL, error_message, message_size) == 0U) {
            free(error_message);
            fputs("Regex error\n", stderr);
            return EXIT_FAILURE;
        }

        fprintf(stderr, "Regex error: %s\n", error_message);
        free(error_message);
        return EXIT_FAILURE;
    }

    puts(matches ? "true" : "false");
    return EXIT_SUCCESS;
}