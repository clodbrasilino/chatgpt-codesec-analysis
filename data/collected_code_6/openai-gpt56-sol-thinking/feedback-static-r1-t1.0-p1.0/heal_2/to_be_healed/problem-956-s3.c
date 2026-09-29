#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <regex.h>

enum SplitStatus {
    SPLIT_SUCCESS = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_OUT_OF_MEMORY,
    SPLIT_REGEX_ERROR
};

static size_t string_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
}

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
    size_t i;

    if (strings == NULL || count == NULL || capacity == NULL ||
        start == NULL || *count > *capacity) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (*count == *capacity) {
        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return SPLIT_OUT_OF_MEMORY;
            }

            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*resized)) {
            return SPLIT_OUT_OF_MEMORY;
        }

        resized = realloc(*strings, new_capacity * sizeof(*resized));
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

    for (i = 0; i < length; ++i) {
        copy[i] = start[i];
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
    input_length = string_length(input);

    regex_status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_status != 0) {
        return SPLIT_REGEX_ERROR;
    }

    while (search_offset < input_length) {
        size_t remaining = input_length - search_offset;
        size_t relative_start;
        size_t relative_end;
        size_t match_start;
        size_t match_end;

        regex_status = regexec(&regex, input + search_offset, 1, &match, 0);
        if (regex_status == REG_NOMATCH) {
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
             */
            match.rm_eo <= match.rm_so) {
            regfree(&regex);
            free_string_array(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        /* Possible weaknesses found:
         *  relative_start is assigned '(unsigned long)match.rm_so' here.
         */
        relative_start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'relative_end=(unsigned long)match.rm_eo', assigned value is less than symbolic=relative_start
         */
        relative_end = (size_t)match.rm_eo;

        /* Possible weaknesses found:
         *  Condition 'relative_start>=relative_end' is always true [knownConditionTrueFalse]
         *  Condition 'relative_start>=relative_end' is always true
         */
        if (relative_start >= relative_end || relative_end > remaining) {
            regfree(&regex);
            free_string_array(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        match_start = search_offset + relative_start;
        match_end = search_offset + relative_end;

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
                           input + token_start,
                           input_length - token_start);

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
int main(int argc, char *const argv[])
{
    char **parts = NULL;
    size_t count = 0;
    size_t i;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "split");
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