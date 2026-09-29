#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    REMOVE_SUCCESS = 0,
    REMOVE_INVALID_ARGUMENT,
    REMOVE_MEMORY_FAILURE,
    REMOVE_REGEX_FAILURE,
    REMOVE_RANGE_FAILURE
} RemoveResult;

RemoveResult remove_lowercase_substrings(const char *input, char **output)
{
    regex_t regex;
    regmatch_t match;
    size_t input_length;
    size_t input_offset = 0;
    size_t output_offset = 0;
    int regex_result;

    if (output == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    *output = NULL;

    if (input == NULL) {
        return REMOVE_INVALID_ARGUMENT;
    }

    regex_result = regcomp(&regex, "[[:lower:]]+", REG_EXTENDED);
    if (regex_result != 0) {
        return REMOVE_REGEX_FAILURE;
    }

    input_length = strlen(input);
    if (input_length == SIZE_MAX) {
        regfree(&regex);
        return REMOVE_RANGE_FAILURE;
    }

    *output = malloc(input_length + 1U);
    if (*output == NULL) {
        regfree(&regex);
        return REMOVE_MEMORY_FAILURE;
    }

    while (input_offset < input_length) {
        size_t remaining = input_length - input_offset;
        size_t match_start;
        size_t match_end;

        regex_result = regexec(&regex, input + input_offset, 1, &match, 0);

        if (regex_result == REG_NOMATCH) {
            memcpy(*output + output_offset, input + input_offset, remaining);
            output_offset += remaining;
            break;
        }

        if (regex_result != 0 || match.rm_so < 0 ||
            match.rm_eo < match.rm_so ||
            (uintmax_t)match.rm_so > (uintmax_t)remaining ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            free(*output);
            *output = NULL;
            regfree(&regex);
            return regex_result != 0
                       ? REMOVE_REGEX_FAILURE
                       : REMOVE_RANGE_FAILURE;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start > input_length - output_offset) {
            free(*output);
            *output = NULL;
            regfree(&regex);
            return REMOVE_RANGE_FAILURE;
        }

        memcpy(*output + output_offset, input + input_offset, match_start);
        output_offset += match_start;
        input_offset += match_end;
    }

    (*output)[output_offset] = '\0';
    regfree(&regex);
    return REMOVE_SUCCESS;
}

int main(int argc, char *argv[])
{
    char *result = NULL;
    RemoveResult status;

    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s <string>\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    status = remove_lowercase_substrings(argv[1], &result);
    if (status != REMOVE_SUCCESS) {
        if (fprintf(stderr, "Failed to process the input string.\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}