#include <inttypes.h>
#include <regex.h>
#include <stdint.h>
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

static int offset_to_size(regoff_t offset, size_t *value)
{
    uintmax_t converted;

    if (value == NULL || offset < 0) {
        return -1;
    }

    converted = (uintmax_t)offset;
    if (converted > (uintmax_t)SIZE_MAX) {
        return -1;
    }

    *value = (size_t)converted;
    return 0;
}

static int write_all(FILE *output, const char *data, size_t length)
{
    while (length > 0) {
        size_t written = fwrite(data, 1, length, output);

        if (written == 0) {
            return -1;
        }

        data += written;
        length -= written;
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
        report_regex_error(result, NULL);
        return -1;
    }

    cursor = input;
    remaining = strlen(input);

    for (;;) {
        regmatch_t match;
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

        if (offset_to_size(match.rm_so, &start) != 0 ||
            offset_to_size(match.rm_eo, &end) != 0 ||
            end <= start ||
            end > remaining) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        length = end - start;

        if (write_all(output, cursor + start, length) != 0 ||
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
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1], stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}