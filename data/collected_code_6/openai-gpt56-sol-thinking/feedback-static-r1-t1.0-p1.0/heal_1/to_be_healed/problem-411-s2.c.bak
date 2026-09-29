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

    result = malloc(input_length + 1);
    if (result == NULL) {
        return CONVERT_NO_MEMORY;
    }

    regex_status = regcomp(&regex, pattern, REG_EXTENDED);
    if (regex_status != 0) {
        free(result);
        return CONVERT_REGEX_ERROR;
    }

    while ((regex_status = regexec(&regex, input + read_offset, 2, matches, 0)) == 0) {
        size_t remaining = input_length - read_offset;
        size_t match_start;
        size_t match_end;

        if (matches[0].rm_so < 0 || matches[0].rm_eo <= matches[0].rm_so) {
            regfree(&regex);
            free(result);
            return CONVERT_REGEX_ERROR;
        }

        match_start = (size_t)matches[0].rm_so;
        match_end = (size_t)matches[0].rm_eo;

        if (match_end > remaining || write_offset > input_length - match_start) {
            regfree(&regex);
            free(result);
            return CONVERT_REGEX_ERROR;
        }

        memcpy(result + write_offset, input + read_offset, match_start);
        write_offset += match_start;

        if (matches[1].rm_so >= 0) {
            size_t capture_start = (size_t)matches[1].rm_so;
            size_t capture_end = (size_t)matches[1].rm_eo;

            if (capture_end != capture_start + 1 ||
                capture_start < match_start ||
                capture_end > match_end ||
                write_offset >= input_length) {
                regfree(&regex);
                free(result);
                return CONVERT_REGEX_ERROR;
            }

            result[write_offset++] =
                (char)toupper((unsigned char)input[read_offset + capture_start]);
        }

        read_offset += match_end;
    }

    if (regex_status != REG_NOMATCH) {
        regfree(&regex);
        free(result);
        return CONVERT_REGEX_ERROR;
    }

    if (write_offset > input_length - (input_length - read_offset)) {
        regfree(&regex);
        free(result);
        return CONVERT_REGEX_ERROR;
    }

    memcpy(result + write_offset, input + read_offset,
           input_length - read_offset + 1);

    regfree(&regex);
    *output = result;
    return CONVERT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char *camel_case = NULL;
    ConvertStatus status;
    int output_status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s snake_case_string\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = snake_to_camel(argv[1], &camel_case);
    if (status != CONVERT_SUCCESS) {
        fputs("Failed to convert the input string.\n", stderr);
        return EXIT_FAILURE;
    }

    output_status = printf("%s\n", camel_case);
    free(camel_case);

    if (output_status < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}