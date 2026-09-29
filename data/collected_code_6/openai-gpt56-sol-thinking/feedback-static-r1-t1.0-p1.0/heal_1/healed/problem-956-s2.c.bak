#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    SPLIT_OK = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_MEMORY_ERROR,
    SPLIT_REGEX_ERROR
};

static void free_split(char **parts, size_t count)
{
    size_t i;

    for (i = 0; i < count; ++i) {
        free(parts[i]);
    }

    free(parts);
}

static int append_part(
    char ***parts,
    size_t *count,
    size_t *capacity,
    const char *start,
    size_t length)
{
    char *part;

    if (*count == *capacity) {
        size_t new_capacity;
        char **resized;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > (SIZE_MAX - 1) / 2) {
                return SPLIT_MEMORY_ERROR;
            }

            new_capacity = *capacity * 2;
        }

        if (new_capacity + 1 > SIZE_MAX / sizeof(*resized)) {
            return SPLIT_MEMORY_ERROR;
        }

        resized = realloc(*parts, (new_capacity + 1) * sizeof(*resized));
        if (resized == NULL) {
            return SPLIT_MEMORY_ERROR;
        }

        *parts = resized;
        *capacity = new_capacity;
        (*parts)[*count] = NULL;
    }

    if (length == SIZE_MAX) {
        return SPLIT_MEMORY_ERROR;
    }

    part = malloc(length + 1);
    if (part == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    if (length != 0) {
        memcpy(part, start, length);
    }

    part[length] = '\0';
    (*parts)[*count] = part;
    ++(*count);
    (*parts)[*count] = NULL;

    return SPLIT_OK;
}

int split_at_uppercase(const char *input, char ***parts_out, size_t *count_out)
{
    regex_t regex;
    regmatch_t match;
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t input_length;
    size_t search_offset = 0;
    size_t segment_start = 0;
    int result;

    if (input == NULL || parts_out == NULL || count_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *parts_out = NULL;
    *count_out = 0;
    input_length = strlen(input);

    result = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (result != 0) {
        return SPLIT_REGEX_ERROR;
    }

    while (search_offset < input_length) {
        result = regexec(
            &regex,
            input + search_offset,
            1,
            &match,
            0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo >
                (uintmax_t)(input_length - search_offset)) {
            regfree(&regex);
            free_split(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        {
            size_t match_start = search_offset + (size_t)match.rm_so;
            size_t next_offset = search_offset + (size_t)match.rm_eo;

            if (match_start > segment_start) {
                result = append_part(
                    &parts,
                    &count,
                    &capacity,
                    input + segment_start,
                    match_start - segment_start);

                if (result != SPLIT_OK) {
                    regfree(&regex);
                    free_split(parts, count);
                    return result;
                }
            }

            segment_start = match_start;
            search_offset = next_offset;
        }
    }

    result = append_part(
        &parts,
        &count,
        &capacity,
        input + segment_start,
        input_length - segment_start);

    regfree(&regex);

    if (result != SPLIT_OK) {
        free_split(parts, count);
        return result;
    }

    *parts_out = parts;
    *count_out = count;

    return SPLIT_OK;
}

int main(int argc, char **argv)
{
    char **parts;
    size_t count;
    size_t i;
    int result;
    int exit_status = EXIT_SUCCESS;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = split_at_uppercase(argv[1], &parts, &count);
    if (result != SPLIT_OK) {
        fprintf(stderr, "Failed to split the string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            exit_status = EXIT_FAILURE;
            break;
        }
    }

    free_split(parts, count);

    return exit_status;
}