#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t size = regerror(error_code, regex, NULL, 0);

    if (size == 0) {
        fputs("Unknown regex error\n", stderr);
        return;
    }

    char *message = malloc(size);

    if (message == NULL) {
        fputs("Unable to allocate memory for regex error message\n", stderr);
        return;
    }

    regerror(error_code, regex, message, size);
    fprintf(stderr, "Regex error: %s\n", message);
    free(message);
}

int find_sequences(const char *text)
{
    regex_t regex;
    const char *cursor;
    size_t remaining;
    int result;

    if (text == NULL) {
        fputs("Input string is NULL\n", stderr);
        return -1;
    }

    result = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        return -1;
    }

    cursor = text;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    remaining = strlen(text);

    while (remaining != 0) {
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

        if (match.rm_so < 0 || match.rm_eo < 0) {
            fputs("Invalid regex match range\n", stderr);
            regfree(&regex);
            return -1;
        }

        uintmax_t start_value = (uintmax_t)match.rm_so;
        uintmax_t end_value = (uintmax_t)match.rm_eo;

        if (end_value <= start_value ||
            start_value > (uintmax_t)SIZE_MAX ||
            end_value > (uintmax_t)SIZE_MAX) {
            fputs("Invalid regex match range\n", stderr);
            regfree(&regex);
            return -1;
        }

        size_t start = (size_t)start_value;
        size_t end = (size_t)end_value;

        if (start >= end || end > remaining) {
            fputs("Invalid regex match range\n", stderr);
            regfree(&regex);
            return -1;
        }

        size_t length = end - start;

        if (fwrite(cursor + start, length, 1, stdout) != 1) {
            fputs("Failed to write output\n", stderr);
            regfree(&regex);
            return -1;
        }

        if (fputc('\n', stdout) == EOF) {
            fputs("Failed to write output\n", stderr);
            regfree(&regex);
            return -1;
        }

        cursor += end;
        remaining -= end;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}