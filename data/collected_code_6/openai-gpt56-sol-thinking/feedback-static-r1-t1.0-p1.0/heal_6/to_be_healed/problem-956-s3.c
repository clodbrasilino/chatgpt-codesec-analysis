#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
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

static enum SplitStatus append_string(char ***strings,
                                      size_t *count,
                                      size_t *capacity,
                                      const char *start,
                                      size_t length)
{
    char **resized;
    char *copy;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;

    if (strings == NULL || count == NULL || capacity == NULL ||
        start == NULL || *count > *capacity ||
        (*capacity != 0 && *strings == NULL)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length > SIZE_MAX - 1) {
        return SPLIT_OUT_OF_MEMORY;
    }

    if (*count == *capacity) {
        if (*capacity == 0) {
            new_capacity = 4;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return SPLIT_OUT_OF_MEMORY;
            }

            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(**strings)) {
            return SPLIT_OUT_OF_MEMORY;
        }

        resized = realloc(*strings, new_capacity * sizeof(*resized));
        if (resized == NULL) {
            return SPLIT_OUT_OF_MEMORY;
        }

        *strings = resized;
        *capacity = new_capacity;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return SPLIT_OUT_OF_MEMORY;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    (*strings)[*count] = copy;
    ++*count;

    return SPLIT_SUCCESS;
}

static enum SplitStatus split_at_uppercase(const char *input,
                                           char ***parts_out,
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
    enum SplitStatus status = SPLIT_SUCCESS;

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
        size_t remaining = input_length - search_offset;
        size_t relative_start;
        size_t relative_end;
        size_t match_start;
        size_t match_end;

        regex_status = regexec(&regex, input + search_offset, 1, &match, 0);

        if (regex_status == REG_NOMATCH) {
            break;
        }

        if (regex_status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            status = SPLIT_REGEX_ERROR;
            goto cleanup;
        }

        relative_start = (size_t)match.rm_so;
        relative_end = (size_t)match.rm_eo;
        match_start = search_offset + relative_start;
        match_end = search_offset + relative_end;

        if (match_start > token_start) {
            status = append_string(&parts,
                                   &count,
                                   &capacity,
                                   input + token_start,
                                   match_start - token_start);
            if (status != SPLIT_SUCCESS) {
                goto cleanup;
            }
        }

        token_start = match_start;
        search_offset = match_end;
    }

    status = append_string(&parts,
                           &count,
                           &capacity,
                           input + token_start,
                           input_length - token_start);
    if (status != SPLIT_SUCCESS) {
        goto cleanup;
    }

    regfree(&regex);
    *parts_out = parts;
    *count_out = count;
    return SPLIT_SUCCESS;

cleanup:
    regfree(&regex);
    free_string_array(parts, count);
    return status;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *program_name;
    const char *input;
    char **parts = NULL;
    size_t count = 0;
    size_t i;
    enum SplitStatus status;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "split";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    input = argv[1];
    status = split_at_uppercase(input, &parts, &count);

    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Unable to split the string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            free_string_array(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_string_array(parts, count);
    return EXIT_SUCCESS;
}