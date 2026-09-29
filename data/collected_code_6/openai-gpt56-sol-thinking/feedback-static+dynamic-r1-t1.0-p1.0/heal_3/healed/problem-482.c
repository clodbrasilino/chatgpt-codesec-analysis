#define _POSIX_C_SOURCE 200809L

#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH ((size_t)1048576)

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

static int find_sequences(const char *input, size_t input_length, FILE *output)
{
    static const char pattern[] = "[A-Z][a-z]+";
    regex_t regex;
    regmatch_t match;
    char *buffer;
    char *cursor;
    size_t remaining;
    int result;

    if (input == NULL || output == NULL || input_length > MAX_INPUT_LENGTH) {
        fputs("Invalid function argument\n", stderr);
        return -1;
    }

    if (memchr(input, '\0', input_length) != NULL) {
        fputs("Input contains an embedded null character\n", stderr);
        return -1;
    }

    buffer = malloc(input_length + 1);
    if (buffer == NULL) {
        fputs("Unable to allocate memory for input\n", stderr);
        return -1;
    }

    memcpy(buffer, input, input_length);
    buffer[input_length] = '\0';

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        free(buffer);
        return -1;
    }

    cursor = buffer;
    remaining = input_length;

    for (;;) {
        size_t start;
        size_t end;
        size_t match_length;

        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        if (match.rm_so < 0 ||
            match.rm_eo < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;
        match_length = end - start;

        if (fwrite(cursor + start, 1, match_length, output) != match_length ||
            fputc('\n', output) == EOF) {
            fputs("Failed to write output\n", stderr);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        cursor += end;
        remaining -= end;
    }

    regfree(&regex);
    free(buffer);

    if (fflush(output) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    const char *program_name;
    const char *input;
    size_t input_length;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "program";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = strnlen(input, MAX_INPUT_LENGTH + 1);

    if (input_length > MAX_INPUT_LENGTH) {
        fprintf(stderr, "Input exceeds the maximum length of %zu bytes\n",
                MAX_INPUT_LENGTH);
        return EXIT_FAILURE;
    }

    if (find_sequences(input, input_length, stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}