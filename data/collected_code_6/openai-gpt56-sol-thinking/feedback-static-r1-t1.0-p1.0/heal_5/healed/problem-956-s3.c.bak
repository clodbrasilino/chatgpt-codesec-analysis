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

static enum SplitStatus append_string(char ***strings,
                                      size_t *count,
                                      size_t *capacity,
                                      const char *start,
                                      size_t length)
{
    char *copy;

    if (strings == NULL || count == NULL || capacity == NULL ||
        (start == NULL && length != 0)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (*count == *capacity) {
        char **resized;
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

    if (length != 0) {
        memcpy(copy, start, length);
    }

    copy[length] = '\0';
    (*strings)[*count] = copy;
    ++(*count);

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
    enum SplitStatus status;

    if (input == NULL || parts_out == NULL || count_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *parts_out = NULL;
    *count_out = 0;
    input_length = strlen(input);

    regex_status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_status != 0) {
        return SPLIT_REGEX_ERROR;
    }

    while (search_offset < input_length) {
        size_t remaining = input_length - search_offset;
        size_t match_start;
        size_t match_end;

        regex_status = regexec(&regex, input + search_offset, 1, &match, 0);

        if (regex_status == REG_NOMATCH) {
            break;
        }

        if (regex_status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > remaining) {
            regfree(&regex);
            free_string_array(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        match_start = search_offset + (size_t)match.rm_so;
        match_end = search_offset + (size_t)match.rm_eo;

        if (match_start > token_start) {
            status = append_string(&parts,
                                   &count,
                                   &capacity,
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

    status = append_string(&parts,
                           &count,
                           &capacity,
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

int main(int argc, char * const argv[])
{
    char **parts = NULL;
    size_t count = 0;
    size_t i;
    enum SplitStatus status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = split_at_uppercase(argv[1], &parts, &count);
    if (status != SPLIT_SUCCESS) {
        fputs("Unable to split the string\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        puts(parts[i]);
    }

    free_string_array(parts, count);

    return EXIT_SUCCESS;
}