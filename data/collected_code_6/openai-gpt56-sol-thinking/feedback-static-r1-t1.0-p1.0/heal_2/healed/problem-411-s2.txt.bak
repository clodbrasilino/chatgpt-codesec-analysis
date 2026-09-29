#include <ctype.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    CONVERT_SUCCESS,
    CONVERT_INVALID_ARGUMENT,
    CONVERT_NO_MEMORY,
    CONVERT_REGEX_ERROR
} ConvertStatus;

ConvertStatus snake_to_camel(const char *input, char **output)
{
    static const char pattern[] = "_+([A-Za-z0-9])?";
    regex_t regex;
    regmatch_t matches[2];
    char *result;
    size_t input_length;
    size_t read_offset = 0;
    size_t write_offset = 0;
    int regex_status;

    if (input == NULL || output == NULL) {
        return CONVERT_INVALID_ARGUMENT;
    }

    *output = NULL;
    input_length = strlen(input);

    if (input_length == SIZE_MAX) {
        return CONVERT_NO_MEMORY;
    }

    regex_status = regcomp(&regex, pattern, REG_EXTENDED);
    if (regex_status != 0) {
        return CONVERT_REGEX_ERROR;
    }

    result = malloc(input_length + 1);
    if (result == NULL) {
        regfree(&regex);
        return CONVERT_NO_MEMORY;
    }

    while ((regex_status = regexec(&regex, input + read_offset,
                                   2, matches, 0)) == 0) {
        size_t remaining = input_length - read_offset;
        size_t match_start;
        size_t match_end;

        if (matches[0].rm_so < 0 ||
            matches[0].rm_eo <= matches[0].rm_so) {
            goto regex_error;
        }

        match_start = (size_t)matches[0].rm_so;
        match_end = (size_t)matches[0].rm_eo;

        if (match_start > remaining ||
            match_end > remaining ||
            write_offset > input_length - match_start) {
            goto regex_error;
        }

        memcpy(result + write_offset,
               input + read_offset,
               match_start);
        write_offset += match_start;

        if ((matches[1].rm_so < 0) != (matches[1].rm_eo < 0)) {
            goto regex_error;
        }

        if (matches[1].rm_so >= 0) {
            size_t capture_start;
            size_t capture_end;

            if (matches[1].rm_eo <= matches[1].rm_so) {
                goto regex_error;
            }

            capture_start = (size_t)matches[1].rm_so;
            capture_end = (size_t)matches[1].rm_eo;

            if (capture_end != capture_start + 1 ||
                capture_start < match_start ||
                capture_end > match_end ||
                write_offset >= input_length) {
                goto regex_error;
            }

            result[write_offset++] = (char)toupper(
                (unsigned char)input[read_offset + capture_start]);
        }

        read_offset += match_end;
    }

    if (regex_status != REG_NOMATCH ||
        read_offset > input_length ||
        write_offset > read_offset) {
        goto regex_error;
    }

    memcpy(result + write_offset,
           input + read_offset,
           input_length - read_offset + 1);

    regfree(&regex);
    *output = result;

    return CONVERT_SUCCESS;

regex_error:
    regfree(&regex);
    free(result);
    return CONVERT_REGEX_ERROR;
}

int main(int argc, char *const argv[])
{
    const char *program_name;
    char *camel_case = NULL;
    ConvertStatus status;
    int output_status;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "snake_to_camel";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", program_name);
        return EXIT_FAILURE;
    }

    status = snake_to_camel(argv[1], &camel_case);
    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    output_status = printf("%s\n", camel_case);
    free(camel_case);

    return output_status < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}