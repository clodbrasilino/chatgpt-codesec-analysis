#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stdbool.h>
#include <stddef.h>
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

static void print_regex_error(int error_code)
{
    size_t required_size;
    char *error_message;

    required_size = regerror(error_code, NULL, NULL, 0);
    if (required_size == 0) {
        fputs("Regex error\n", stderr);
        return;
    }

    error_message = malloc(required_size);
    if (error_message == NULL) {
        fputs("Regex error: unable to allocate error message\n", stderr);
        return;
    }

    if (regerror(error_code, NULL, error_message, required_size) == 0) {
        fputs("Regex error\n", stderr);
    } else {
        fprintf(stderr, "Regex error: %s\n", error_message);
    }

    free(error_message);
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    const char *program_name = "program";
    int error_code;
    bool matches;

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Usage: %s <string> <regex>\n", program_name);
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