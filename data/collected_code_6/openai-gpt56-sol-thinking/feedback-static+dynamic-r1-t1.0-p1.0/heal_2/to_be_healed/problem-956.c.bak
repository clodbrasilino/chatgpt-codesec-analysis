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
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(parts[i]);
    }

    free(parts);
}

static SplitResult append_part(char ***parts, size_t *count, size_t *capacity,
                               const char *start, size_t length)
{
    char *part;
    size_t required;

    if (length == SIZE_MAX || *count > SIZE_MAX - 2) {
        return SPLIT_OUT_OF_MEMORY;
    }

    required = *count + 2;

    if (required > *capacity) {
        char **resized;
        size_t new_capacity = *capacity == 0 ? 4 : *capacity;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(**parts)) {
            return SPLIT_OUT_OF_MEMORY;
        }

        resized = realloc(*parts, new_capacity * sizeof(**parts));
        if (resized == NULL) {
            return SPLIT_OUT_OF_MEMORY;
        }

        *parts = resized;
        *capacity = new_capacity;
    }

    part = malloc(length + 1);
    if (part == NULL) {
        return SPLIT_OUT_OF_MEMORY;
    }

    memcpy(part, start, length);
    part[length] = '\0';

    (*parts)[*count] = part;
    ++(*count);
    (*parts)[*count] = NULL;

    return SPLIT_SUCCESS;
}

static SplitResult split_at_uppercase(const char *input, char ***output,
                                      size_t *output_count)
{
    regex_t regex;
    regmatch_t match;
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t input_length;
    size_t search_offset = 0;
    size_t segment_start = 0;
    int regex_result;

    if (input == NULL || output == NULL || output_count == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *output = NULL;
    *output_count = 0;

    regex_result = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_result != 0) {
        return SPLIT_REGEX_ERROR;
    }

    input_length = strlen(input);

    while (search_offset < input_length) {
        size_t remaining = input_length - search_offset;

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

        {
            size_t match_start = search_offset + (size_t)match.rm_so;

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
        }

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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char **parts;
    size_t count;
    size_t i;
    SplitResult result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (setlocale(LC_CTYPE, "") == NULL) {
        fprintf(stderr, "Unable to initialize locale\n");
        return EXIT_FAILURE;
    }

    result = split_at_uppercase(argv[1], &parts, &count);
    if (result != SPLIT_SUCCESS) {
        fprintf(stderr, "Unable to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
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