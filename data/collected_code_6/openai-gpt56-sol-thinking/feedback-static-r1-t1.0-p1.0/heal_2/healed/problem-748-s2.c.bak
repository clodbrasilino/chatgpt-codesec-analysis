#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

typedef enum {
    SPACE_STATUS_OK = 0,
    SPACE_STATUS_INVALID_ARGUMENT,
    SPACE_STATUS_OVERFLOW,
    SPACE_STATUS_ALLOCATION_FAILURE,
    SPACE_STATUS_REGEX_FAILURE
} SpaceStatus;

SpaceStatus add_spaces_between_words(const char *input, char **result)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    size_t input_length;
    size_t output_length = 0U;
    size_t cursor_offset = 0U;
    size_t capacity;
    int regex_status;

    if (input == NULL || result == NULL) {
        return SPACE_STATUS_INVALID_ARGUMENT;
    }

    *result = NULL;
    input_length = strlen(input);

    if (input_length > (SIZE_MAX - 1U) / 2U) {
        return SPACE_STATUS_OVERFLOW;
    }

    regex_status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_status != 0) {
        return SPACE_STATUS_REGEX_FAILURE;
    }

    capacity = input_length * 2U + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        regfree(&regex);
        return SPACE_STATUS_ALLOCATION_FAILURE;
    }

    while (cursor_offset < input_length) {
        const char *cursor = input + cursor_offset;
        size_t remaining = input_length - cursor_offset;
        size_t match_start;
        size_t match_end;
        size_t absolute_position;

        regex_status = regexec(&regex, cursor, 1U, &match, 0);

        if (regex_status == REG_NOMATCH) {
            memcpy(output + output_length, cursor, remaining);
            output_length += remaining;
            cursor_offset = input_length;
            break;
        }

        if (regex_status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so) {
            free(output);
            regfree(&regex);
            return SPACE_STATUS_REGEX_FAILURE;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start > remaining || match_end > remaining) {
            free(output);
            regfree(&regex);
            return SPACE_STATUS_REGEX_FAILURE;
        }

        absolute_position = cursor_offset + match_start;

        memcpy(output + output_length, cursor, match_start);
        output_length += match_start;

        if (absolute_position > 0U &&
            !isspace((unsigned char)input[absolute_position - 1U])) {
            output[output_length++] = ' ';
        }

        memcpy(output + output_length,
               cursor + match_start,
               match_end - match_start);
        output_length += match_end - match_start;
        cursor_offset += match_end;
    }

    output[output_length] = '\0';

    regfree(&regex);
    *result = output;

    return SPACE_STATUS_OK;
}

int main(int argc, char *argv[const])
{
    char *result = NULL;
    SpaceStatus status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = add_spaces_between_words(argv[1], &result);
    if (status != SPACE_STATUS_OK) {
        fprintf(stderr, "Failed to process the string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}