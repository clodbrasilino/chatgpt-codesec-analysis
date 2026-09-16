#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t size = regerror(error_code, regex, NULL, 0);

    if (size == 0) {
        fputs("Regular expression error\n", stderr);
        return;
    }

    char *message = malloc(size);
    if (message == NULL) {
        fputs("Regular expression error\n", stderr);
        return;
    }

    regerror(error_code, regex, message, size);
    fprintf(stderr, "Regular expression error: %s\n", message);
    free(message);
}

static int remove_lowercase_substrings(char *string)
{
    if (string == NULL) {
        fputs("Invalid string\n", stderr);
        return -1;
    }

    regex_t regex;
    int result = regcomp(&regex, "[a-z]+", REG_EXTENDED);

    if (result != 0) {
        report_regex_error(result, &regex);
        return -1;
    }

    char *cursor = string;

    for (;;) {
        regmatch_t match;

        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_so > SIZE_MAX ||
            (uintmax_t)match.rm_eo > SIZE_MAX) {
            fputs("Invalid regular expression match\n", stderr);
            regfree(&regex);
            return -1;
        }

        size_t start = (size_t)match.rm_so;
        size_t end = (size_t)match.rm_eo;
        size_t remaining = strlen(cursor);

        if (end > remaining) {
            fputs("Regular expression match exceeds string bounds\n", stderr);
            regfree(&regex);
            return -1;
        }

        memmove(cursor + start, cursor + end, remaining - end + 1);
        cursor += start;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input = argv[1];
    size_t length = strlen(input);

    if (length == SIZE_MAX) {
        fputs("Input string is too large\n", stderr);
        return EXIT_FAILURE;
    }

    char *string = malloc(length + 1);
    if (string == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    memcpy(string, input, length + 1);

    if (remove_lowercase_substrings(string) != 0) {
        free(string);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", string) < 0) {
        fputs("Output error\n", stderr);
        free(string);
        return EXIT_FAILURE;
    }

    free(string);
    return EXIT_SUCCESS;
}