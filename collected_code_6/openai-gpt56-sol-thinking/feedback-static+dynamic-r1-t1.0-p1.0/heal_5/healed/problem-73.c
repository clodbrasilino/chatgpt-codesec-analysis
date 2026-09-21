#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum SplitStatus {
    SPLIT_SUCCESS = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_REGEX_ERROR,
    SPLIT_MEMORY_ERROR,
    SPLIT_EMPTY_DELIMITER_MATCH
};

static void free_split_result(char **parts, size_t count)
{
    if (parts == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(parts[i]);
    }

    free(parts);
}

static int measure_string(const char *string, size_t *length_out)
{
    size_t length = 0;

    if (string == NULL || length_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    for (;;) {
        if (string[length] == '\0') {
            *length_out = length;
            return SPLIT_SUCCESS;
        }

        if (length == SIZE_MAX - 1) {
            return SPLIT_INVALID_ARGUMENT;
        }

        ++length;
    }
}

static int grow_parts(char ***parts, size_t *capacity)
{
    size_t maximum_capacity;
    size_t new_capacity;
    char **resized;

    if (parts == NULL || capacity == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    maximum_capacity = SIZE_MAX / sizeof **parts;

    if (*capacity >= maximum_capacity) {
        return SPLIT_MEMORY_ERROR;
    }

    if (*capacity == 0) {
        new_capacity = maximum_capacity < 8 ? maximum_capacity : 8;
    } else {
        size_t growth = *capacity / 2 + 1;
        size_t available = maximum_capacity - *capacity;

        new_capacity = growth > available
                     ? maximum_capacity
                     : *capacity + growth;
    }

    if (new_capacity <= *capacity) {
        return SPLIT_MEMORY_ERROR;
    }

    resized = realloc(*parts, new_capacity * sizeof *resized);
    if (resized == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    *parts = resized;
    *capacity = new_capacity;

    return SPLIT_SUCCESS;
}

static int append_part(char ***parts, size_t *count, size_t *capacity,
                       const char *start, size_t length)
{
    char *part;

    if (parts == NULL || count == NULL || capacity == NULL ||
        start == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (*count > *capacity || length == SIZE_MAX) {
        return SPLIT_MEMORY_ERROR;
    }

    if (*count == *capacity) {
        int status = grow_parts(parts, capacity);

        if (status != SPLIT_SUCCESS) {
            return status;
        }
    }

    part = malloc(length + 1);
    if (part == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        part[i] = start[i];
    }

    part[length] = '\0';
    (*parts)[*count] = part;
    ++*count;

    return SPLIT_SUCCESS;
}

static int decode_match(const regmatch_t *match, size_t remaining,
                        size_t *match_start, size_t *match_end)
{
    uintmax_t start;
    uintmax_t end;

    if (match == NULL || match_start == NULL || match_end == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (match->rm_so < 0 || match->rm_eo < 0) {
        return SPLIT_REGEX_ERROR;
    }

    start = (uintmax_t)match->rm_so;
    end = (uintmax_t)match->rm_eo;

    if (end < start ||
        start > (uintmax_t)remaining ||
        end > (uintmax_t)remaining) {
        return SPLIT_REGEX_ERROR;
    }

    if (start == end) {
        return SPLIT_EMPTY_DELIMITER_MATCH;
    }

    *match_start = (size_t)start;
    *match_end = (size_t)end;

    return SPLIT_SUCCESS;
}

static int split_regex(const char *input, const char *delimiter_pattern,
                       char ***parts_out, size_t *count_out)
{
    regex_t regex;
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    size_t input_length;
    int status;
    int regex_status;

    if (parts_out == NULL || count_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *parts_out = NULL;
    *count_out = 0;

    if (input == NULL || delimiter_pattern == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    status = measure_string(input, &input_length);
    if (status != SPLIT_SUCCESS) {
        return status;
    }

    regex_status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (regex_status != 0) {
        return SPLIT_REGEX_ERROR;
    }

    status = SPLIT_SUCCESS;

    while (offset <= input_length) {
        regmatch_t match;
        const char *cursor = input + offset;
        size_t remaining = input_length - offset;
        size_t match_start;
        size_t match_end;
        int execution_flags = offset == 0 ? 0 : REG_NOTBOL;

        regex_status = regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_status == REG_NOMATCH) {
            status = append_part(&parts, &count, &capacity,
                                 cursor, remaining);
            break;
        }

        if (regex_status != 0) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        status = decode_match(&match, remaining, &match_start, &match_end);
        if (status != SPLIT_SUCCESS) {
            break;
        }

        status = append_part(&parts, &count, &capacity,
                             cursor, match_start);
        if (status != SPLIT_SUCCESS) {
            break;
        }

        offset += match_end;
    }

    regfree(&regex);

    if (status != SPLIT_SUCCESS) {
        free_split_result(parts, count);
        return status;
    }

    *parts_out = parts;
    *count_out = count;

    return SPLIT_SUCCESS;
}

static const char *split_status_message(int status)
{
    switch (status) {
        case SPLIT_SUCCESS:
            return "success";
        case SPLIT_INVALID_ARGUMENT:
            return "invalid argument";
        case SPLIT_REGEX_ERROR:
            return "invalid or failed regular expression";
        case SPLIT_MEMORY_ERROR:
            return "memory allocation failed";
        case SPLIT_EMPTY_DELIMITER_MATCH:
            return "delimiter expression produced an empty match";
        default:
            return "unknown error";
    }
}

int main(int argc, char **argv)
{
    char **parts = NULL;
    size_t count = 0;
    int output_failed = 0;
    int status;
    const char *program_name;

    program_name = argc > 0 && argv[0] != NULL ? argv[0] : "split";

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n",
                program_name);
        return EXIT_FAILURE;
    }

    status = split_regex(argv[2], argv[1], &parts, &count);
    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Split failed: %s\n",
                split_status_message(status));
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            output_failed = 1;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        output_failed = 1;
    }

    free_split_result(parts, count);

    if (output_failed) {
        fputs("Output failed\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}