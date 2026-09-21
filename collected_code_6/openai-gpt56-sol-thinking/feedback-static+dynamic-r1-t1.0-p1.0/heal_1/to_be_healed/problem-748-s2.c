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
    const char *cursor;
    char *output;
    size_t input_length;
    size_t output_length = 0;
    size_t capacity;
    int regex_status;

    if (input == NULL || result == NULL) {
        return SPACE_STATUS_INVALID_ARGUMENT;
    }

    *result = NULL;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    if (input_length > (SIZE_MAX - 1U) / 2U) {
        return SPACE_STATUS_OVERFLOW;
    }

    capacity = input_length * 2U + 1U;
    output = malloc(capacity);
    if (output == NULL) {
        return SPACE_STATUS_ALLOCATION_FAILURE;
    }

    regex_status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_status != 0) {
        free(output);
        return SPACE_STATUS_REGEX_FAILURE;
    }

    cursor = input;

    for (;;) {
        size_t match_start;
        size_t match_end;
        size_t absolute_position;

        regex_status = regexec(&regex, cursor, 1, &match, 0);
        if (regex_status == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t remaining = strlen(cursor);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + output_length, cursor, remaining);
            output_length += remaining;
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free(output);
            return SPACE_STATUS_REGEX_FAILURE;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;
        absolute_position = (size_t)(cursor - input) + match_start;

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + output_length, cursor, match_start);
        output_length += match_start;

        if (absolute_position > 0U &&
            !isspace((unsigned char)input[absolute_position - 1U])) {
            output[output_length++] = ' ';
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + output_length, cursor + match_start,
               match_end - match_start);
        output_length += match_end - match_start;
        cursor += match_end;
    }

    output[output_length] = '\0';
    regfree(&regex);
    *result = output;

    return SPACE_STATUS_OK;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
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