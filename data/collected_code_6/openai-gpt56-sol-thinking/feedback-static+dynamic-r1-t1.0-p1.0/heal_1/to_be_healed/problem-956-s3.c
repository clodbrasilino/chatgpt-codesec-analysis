#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

enum SplitStatus {
    SPLIT_SUCCESS = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_OUT_OF_MEMORY,
    SPLIT_REGEX_ERROR
};

static void free_string_array(char **strings, size_t count)
{
    size_t i;

    if (strings == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(strings[i]);
    }

    free(strings);
}

static int append_string(char ***strings, size_t *count, size_t *capacity,
                         const char *start, size_t length)
{
    char **resized;
    char *copy;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (*count == *capacity) {
        new_capacity = *capacity == 0 ? 4 : *capacity * 2;

        if (new_capacity < *capacity ||
            new_capacity > SIZE_MAX / sizeof(**strings)) {
            return SPLIT_OUT_OF_MEMORY;
        }

        resized = realloc(*strings, new_capacity * sizeof(**strings));
        if (resized == NULL) {
            return SPLIT_OUT_OF_MEMORY;
        }

        *strings = resized;
        *capacity = new_capacity;
    }

    if (length == SIZE_MAX) {
        return SPLIT_OUT_OF_MEMORY;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return SPLIT_OUT_OF_MEMORY;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, start, length);
    }
    copy[length] = '\0';

    (*strings)[*count] = copy;
    ++(*count);

    return SPLIT_SUCCESS;
}

static int split_at_uppercase(const char *input, char ***parts_out,
                              size_t *count_out)
{
    regex_t regex;
    regmatch_t match;
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t input_length;
    size_t search_offset = 0;
    size_t token_start = 0;
    int regex_status;
    int status;

    if (input == NULL || parts_out == NULL || count_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *parts_out = NULL;
    *count_out = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_length = strlen(input);

    regex_status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_status != 0) {
        return SPLIT_REGEX_ERROR;
    }

    while (search_offset < input_length) {
        size_t match_start;
        size_t match_end;

        regex_status = regexec(&regex, input + search_offset, 1, &match, 0);
        if (regex_status == REG_NOMATCH) {
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free_string_array(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        if ((size_t)match.rm_eo > input_length - search_offset) {
            regfree(&regex);
            free_string_array(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        match_start = search_offset + (size_t)match.rm_so;
        match_end = search_offset + (size_t)match.rm_eo;

        if (match_start > token_start) {
            status = append_string(&parts, &count, &capacity,
                                   input + token_start,
                                   match_start - token_start);
            if (status != SPLIT_SUCCESS) {
                regfree(&regex);
                free_string_array(parts, count);
                return status;
            }
        }

        token_start = match_start;
        search_offset = match_end;
    }

    status = append_string(&parts, &count, &capacity,
                           input + token_start, input_length - token_start);
    regfree(&regex);

    if (status != SPLIT_SUCCESS) {
        free_string_array(parts, count);
        return status;
    }

    *parts_out = parts;
    *count_out = count;

    return SPLIT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char **parts;
    size_t count;
    size_t i;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = split_at_uppercase(argv[1], &parts, &count);
    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Unable to split the string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        puts(parts[i]);
    }

    free_string_array(parts, count);
    return EXIT_SUCCESS;
}