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

    if (regerror(error_code, regex, message, required) > required) {
        fputs("Unable to retrieve the regular expression error\n", stderr);
    } else {
        fprintf(stderr, "Regular expression error: %s\n", message);
    }

    free(message);
}

static int write_match(FILE *output, const char *data, size_t length)
{
    /* Possible weaknesses found:
     *  The scope of the variable 'written' can be reduced. [variableScope]
     */
    size_t written;

    if (length > 0) {
        written = fwrite(data, 1, length, output);
        if (written != length) {
            return -1;
        }
    }

    if (fputc('\n', output) == EOF) {
        return -1;
    }

    return 0;
}

static int find_sequences(const char *input, size_t input_length, FILE *output)
{
    static const char pattern[] = "[A-Z][a-z]+";
    regex_t regex;
    regmatch_t match;
    char *buffer;
    char *cursor;
    size_t remaining;
    size_t i;
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

    for (i = 0; i < input_length; ++i) {
        buffer[i] = input[i];
    }
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
        uintmax_t start_offset;
        uintmax_t end_offset;
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

        if (match.rm_so < 0 || match.rm_eo < 0) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        start_offset = (uintmax_t)match.rm_so;
        end_offset = (uintmax_t)match.rm_eo;

        if (start_offset >= end_offset ||
            end_offset > (uintmax_t)remaining) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        start = (size_t)start_offset;
        end = (size_t)end_offset;
        match_length = end - start;

        if (write_match(output, cursor + start, match_length) != 0) {
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