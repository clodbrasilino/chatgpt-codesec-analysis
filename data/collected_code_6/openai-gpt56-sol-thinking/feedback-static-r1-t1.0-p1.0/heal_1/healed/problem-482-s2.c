#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t size = regerror(error_code, regex, NULL, 0);
    char *message;

    if (size == 0) {
        fputs("Unknown regular expression error\n", stderr);
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

static int write_sequence(const char *sequence, size_t length)
{
    size_t written = 0;

    while (written < length) {
        size_t count = fwrite(sequence + written, 1, length - written, stdout);

        if (count == 0) {
            fputs("Failed to write output\n", stderr);
            return -1;
        }

        written += count;
    }

    if (fputc('\n', stdout) == EOF) {
        fputs("Failed to write output\n", stderr);
        return -1;
    }

    return 0;
}

int find_sequences(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
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

    while (*cursor != '\0') {
        regoff_t start_offset;
        regoff_t end_offset;
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

        start_offset = match.rm_so;
        end_offset = match.rm_eo;

        if (start_offset < 0 || end_offset < 0 ||
            end_offset <= start_offset ||
            (uintmax_t)start_offset > (uintmax_t)SIZE_MAX ||
            (uintmax_t)end_offset > (uintmax_t)SIZE_MAX) {
            fputs("Invalid regex match range\n", stderr);
            regfree(&regex);
            return -1;
        }

        start = (size_t)start_offset;
        end = (size_t)end_offset;
        length = end - start;

        if (write_sequence(cursor + start, length) != 0) {
            regfree(&regex);
            return -1;
        }

        cursor += end;
    }

    regfree(&regex);
    return 0;
}

int main(int argc, char *argv[])
{
    const char *program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "program";

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