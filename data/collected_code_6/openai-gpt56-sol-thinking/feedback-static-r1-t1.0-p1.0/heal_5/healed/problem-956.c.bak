#include <locale.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SPLIT_SUCCESS,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_OUT_OF_MEMORY,
    SPLIT_REGEX_ERROR
} SplitResult;

static void free_split(char **parts, size_t count)
{
    if (parts == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(parts[i]);
    }

    free(parts);
}

static SplitResult append_part(char ***parts, size_t *count, size_t *capacity,
                               const char *start, size_t length)
{
    if (parts == NULL || count == NULL || capacity == NULL || start == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX || *count > SIZE_MAX - 2) {
        return SPLIT_OUT_OF_MEMORY;
    }

    const size_t required = *count + 2;

    if (required > *capacity) {
        size_t new_capacity = (*capacity == 0) ? 4 : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **parts) {
            return SPLIT_OUT_OF_MEMORY;
        }

        char **resized = realloc(*parts, new_capacity * sizeof **parts);
        if (resized == NULL) {
            return SPLIT_OUT_OF_MEMORY;
        }

        *parts = resized;
        *capacity = new_capacity;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return SPLIT_OUT_OF_MEMORY;
    }

    memcpy(part, start, length);
    part[length] = '\0';

    (*parts)[*count] = part;
    ++*count;
    (*parts)[*count] = NULL;

    return SPLIT_SUCCESS;
}

static SplitResult split_at_uppercase(const char *input, char ***output,
                                      size_t *output_count)
{
    if (input == NULL || output == NULL || output_count == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *output = NULL;
    *output_count = 0;

    regex_t regex;
    int regex_result = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_result != 0) {
        return SPLIT_REGEX_ERROR;
    }

    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t search_offset = 0;
    size_t segment_start = 0;
    const size_t input_length = strlen(input);

    while (search_offset < input_length) {
        regmatch_t match;
        const size_t remaining = input_length - search_offset;

        regex_result = regexec(&regex, input + search_offset, 1, &match, 0);

        if (regex_result == REG_NOMATCH) {
            break;
        }

        if (regex_result != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (size_t)match.rm_eo > remaining) {
            free_split(parts, count);
            regfree(&regex);
            return SPLIT_REGEX_ERROR;
        }

        const size_t match_start = search_offset + (size_t)match.rm_so;

        if (match_start > segment_start) {
            SplitResult result = append_part(
                &parts,
                &count,
                &capacity,
                input + segment_start,
                match_start - segment_start
            );

            if (result != SPLIT_SUCCESS) {
                free_split(parts, count);
                regfree(&regex);
                return result;
            }
        }

        segment_start = match_start;
        search_offset += (size_t)match.rm_eo;
    }

    if (segment_start < input_length || count == 0) {
        SplitResult result = append_part(
            &parts,
            &count,
            &capacity,
            input + segment_start,
            input_length - segment_start
        );

        if (result != SPLIT_SUCCESS) {
            free_split(parts, count);
            regfree(&regex);
            return result;
        }
    }

    regfree(&regex);

    *output = parts;
    *output_count = count;

    return SPLIT_SUCCESS;
}

int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    if (setlocale(LC_CTYPE, "") == NULL) {
        fputs("Unable to initialize locale\n", stderr);
        return EXIT_FAILURE;
    }

    char **parts = NULL;
    size_t count = 0;

    const SplitResult result = split_at_uppercase(argv[1], &parts, &count);
    if (result != SPLIT_SUCCESS) {
        fputs("Unable to split string\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%s\n", parts[i]) < 0) {
            free_split(parts, count);
            return EXIT_FAILURE;
        }
    }

    free_split(parts, count);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}