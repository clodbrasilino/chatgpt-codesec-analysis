#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t size;
    char *message;

    size = regerror(error_code, regex, NULL, 0);
    if (size == 0) {
        fputs("Unknown regex error\n", stderr);
        return;
    }

    message = malloc(size);
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
    remaining = strlen(text);

    while (remaining > 0) {
        regmatch_t match;
        uintmax_t start_offset;
        uintmax_t end_offset;
        size_t start;
        size_t end;
        size_t length;

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

        start_offset = (uintmax_t)match.rm_so;
        end_offset = (uintmax_t)match.rm_eo;

        if (start_offset >= end_offset ||
            start_offset > (uintmax_t)SIZE_MAX ||
            end_offset > (uintmax_t)SIZE_MAX ||
            end_offset > (uintmax_t)remaining) {
            fputs("Invalid regex match range\n", stderr);
            regfree(&regex);
            return -1;
        }

        start = (size_t)start_offset;
        end = (size_t)end_offset;
        length = end - start;

        if (fwrite(cursor + start, 1, length, stdout) != length) {
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

int main(int argc, char *argv[])
{
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
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