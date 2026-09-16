#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t required = regerror(error_code, regex, NULL, 0);

    if (required == 0) {
        fputs("Unknown regular expression error\n", stderr);
        return;
    }

    char *message = malloc(required);
    if (message == NULL) {
        fputs("Unable to allocate memory for the error message\n", stderr);
        return;
    }

    (void)regerror(error_code, regex, message, required);
    fprintf(stderr, "Regular expression error: %s\n", message);
    free(message);
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

    for (;;) {
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
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        start_offset = (uintmax_t)match.rm_so;
        end_offset = (uintmax_t)match.rm_eo;

        if (end_offset <= start_offset ||
            start_offset > (uintmax_t)SIZE_MAX ||
            end_offset > (uintmax_t)SIZE_MAX ||
            end_offset > (uintmax_t)remaining) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        start = (size_t)start_offset;
        end = (size_t)end_offset;
        length = end - start;

        if (fwrite(cursor + start, 1, length, output) != length ||
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

int main(int argc, char *argv[const])
{
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    return find_sequences(argv[1], stdout) == 0
               ? EXIT_SUCCESS
               : EXIT_FAILURE;
}