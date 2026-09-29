#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t required = regerror(error_code, regex, NULL, 0);
    char *message;

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

static int find_sequences(const char *input, FILE *output)
{
    static const char pattern[] = "[A-Z][a-z]+";
    regex_t regex;
    regmatch_t match;
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

    for (;;) {
        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        {
            size_t start = (size_t)match.rm_so;
            size_t end = (size_t)match.rm_eo;
            size_t length = end - start;

            if (fwrite(cursor + start, 1, length, output) != length ||
                fputc('\n', output) == EOF) {
                fputs("Failed to write output\n", stderr);
                regfree(&regex);
                return -1;
            }

            cursor += end;
            remaining -= end;
        }
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