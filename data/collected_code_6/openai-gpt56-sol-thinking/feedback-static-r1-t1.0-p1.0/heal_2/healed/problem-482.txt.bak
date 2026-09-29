#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t required;
    char *message;

    required = regerror(error_code, regex, NULL, 0);
    if (required == 0) {
        fputs("Unknown regular expression error\n", stderr);
        return;
    }

    message = malloc(required);
    if (message == NULL) {
        fputs("Unable to allocate memory for the error message\n", stderr);
        return;
    }

    regerror(error_code, regex, message, required);
    fprintf(stderr, "Regular expression error: %s\n", message);
    free(message);
}

static int write_bytes(FILE *output, const char *data, size_t length)
{
    size_t index;

    for (index = 0; index < length; ++index) {
        if (fputc((unsigned char)data[index], output) == EOF) {
            return -1;
        }
    }

    return 0;
}

static int find_sequences(const char *input, FILE *output)
{
    static const char pattern[] = "[A-Z][a-z]+";
    regex_t regex;
    const char *cursor;
    size_t remaining;
    int result;

    if (input == NULL || output == NULL) {
        fputs("Invalid function argument\n", stderr);
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        return -1;
    }

    cursor = input;
    remaining = strlen(input);

    while (remaining != 0) {
        regmatch_t match;
        intmax_t signed_start;
        intmax_t signed_end;
        uintmax_t unsigned_start;
        uintmax_t unsigned_end;
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

        signed_start = (intmax_t)match.rm_so;
        signed_end = (intmax_t)match.rm_eo;

        if (signed_start < 0 || signed_end < 0) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        if (signed_end <= signed_start) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        unsigned_start = (uintmax_t)signed_start;
        unsigned_end = (uintmax_t)signed_end;

        if (unsigned_start > (uintmax_t)remaining ||
            unsigned_end > (uintmax_t)remaining) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        start = (size_t)unsigned_start;
        end = (size_t)unsigned_end;
        length = (size_t)(unsigned_end - unsigned_start);

        if (write_bytes(output, cursor + start, length) != 0 ||
            fputc('\n', output) == EOF) {
            fputs("Failed to write output\n", stderr);
            regfree(&regex);
            return -1;
        }

        cursor += end;
        remaining -= end;
    }

    regfree(&regex);

    if (fflush(output) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1], stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}