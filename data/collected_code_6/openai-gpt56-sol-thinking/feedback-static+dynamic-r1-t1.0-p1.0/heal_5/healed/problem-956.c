#include <locale.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SPLIT_MAX_INPUT_LENGTH ((size_t)16 * 1024 * 1024)

typedef enum {
    SPLIT_SUCCESS,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_INPUT_TOO_LONG,
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

static SplitResult get_input_length(const char *input, size_t *length)
{
    if (input == NULL || length == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    for (size_t i = 0; i <= SPLIT_MAX_INPUT_LENGTH; ++i) {
        if (input[i] == '\0') {
            *length = i;
            return SPLIT_SUCCESS;
        }
    }

    return SPLIT_INPUT_TOO_LONG;
}

static SplitResult append_part(char ***parts, size_t *count, size_t *capacity,
                               const char *start, size_t length)
{
    size_t required;
    char *part;

    if (parts == NULL || count == NULL || capacity == NULL || start == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX || *count > SIZE_MAX - 2) {
        return SPLIT_OUT_OF_MEMORY;
    }

    required = *count + 2;

    if (required > *capacity) {
        size_t new_capacity = *capacity == 0 ? 4 : *capacity;
        char **resized;

        while (new_capacity < required) {
            if (new_capacity > SIZE_MAX / 2) {
                new_capacity = required;
                break;
            }

            new_capacity *= 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(*resized)) {
            return SPLIT_OUT_OF_MEMORY;
        }

        resized = realloc(*parts, new_capacity * sizeof(*resized));
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

    for (size_t i = 0; i < length; ++i) {
        part[i] = start[i];
    }

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
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t input_length = 0;
    size_t search_offset = 0;
    size_t segment_start = 0;
    SplitResult result;
    int regex_result;

    if (output == NULL || output_count == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *output = NULL;
    *output_count = 0;

    result = get_input_length(input, &input_length);
    if (result != SPLIT_SUCCESS) {
        return result;
    }

    regex_result = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (regex_result != 0) {
        return SPLIT_REGEX_ERROR;
    }

    while (search_offset < input_length) {
        regmatch_t match;
        size_t remaining = input_length - search_offset;
        size_t match_start;
        size_t match_end;

        regex_result = regexec(&regex, input + search_offset, 1, &match, 0);

        if (regex_result == REG_NOMATCH) {
            break;
        }

        if (regex_result != 0 ||
            match.rm_so < 0 ||
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_so > (uintmax_t)remaining ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            free_split(parts, count);
            regfree(&regex);
            return SPLIT_REGEX_ERROR;
        }

        match_start = search_offset + (size_t)match.rm_so;
        match_end = search_offset + (size_t)match.rm_eo;

        if (match_start > segment_start) {
            result = append_part(&parts, &count, &capacity,
                                 input + segment_start,
                                 match_start - segment_start);
            if (result != SPLIT_SUCCESS) {
                free_split(parts, count);
                regfree(&regex);
                return result;
            }
        }

        segment_start = match_start;
        search_offset = match_end;
    }

    if (segment_start < input_length || count == 0) {
        result = append_part(&parts, &count, &capacity,
                             input + segment_start,
                             input_length - segment_start);
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

int main(int argc, char **argv)
{
    const char *program_name;
    char **parts = NULL;
    size_t count = 0;
    SplitResult result;

    program_name = argc > 0 && argv != NULL && argv[0] != NULL
                       ? argv[0]
                       : "split";

    if (argc != 2 || argv == NULL || argv[1] == NULL) {
        fprintf(stderr, "Usage: %s <string>\n", program_name);
        return EXIT_FAILURE;
    }

    if (setlocale(LC_CTYPE, "") == NULL) {
        fprintf(stderr, "Unable to initialize locale\n");
        return EXIT_FAILURE;
    }

    result = split_at_uppercase(argv[1], &parts, &count);
    if (result != SPLIT_SUCCESS) {
        if (result == SPLIT_INPUT_TOO_LONG) {
            fprintf(stderr, "Input string is too long\n");
        } else if (result == SPLIT_OUT_OF_MEMORY) {
            fprintf(stderr, "Out of memory\n");
        } else if (result == SPLIT_REGEX_ERROR) {
            fprintf(stderr, "Regular expression error\n");
        } else {
            fprintf(stderr, "Invalid argument\n");
        }

        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
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