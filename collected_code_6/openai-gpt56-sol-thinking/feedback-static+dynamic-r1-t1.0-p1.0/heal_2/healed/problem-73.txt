#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int grow_parts(char ***parts, size_t *capacity)
{
    const size_t maximum_capacity = SIZE_MAX / sizeof **parts;
    size_t new_capacity;
    char **resized;

    if (parts == NULL || capacity == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (*capacity >= maximum_capacity) {
        return SPLIT_MEMORY_ERROR;
    }

    if (*capacity == 0) {
        new_capacity = maximum_capacity < 8 ? maximum_capacity : 8;
    } else {
        const size_t growth = *capacity / 2 + 1;

        if (growth > maximum_capacity - *capacity) {
            new_capacity = maximum_capacity;
        } else {
            new_capacity = *capacity + growth;
        }
    }

    if (new_capacity == 0) {
        return SPLIT_MEMORY_ERROR;
    }

    resized = realloc(*parts, new_capacity * sizeof **parts);
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

    if (parts == NULL || count == NULL || capacity == NULL || start == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (*count > *capacity || length == SIZE_MAX) {
        return SPLIT_MEMORY_ERROR;
    }

    if (*count == *capacity) {
        const int status = grow_parts(parts, capacity);

        if (status != SPLIT_SUCCESS) {
            return status;
        }
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
    ++*count;

    return SPLIT_SUCCESS;
}

static int split_regex(const char *input, size_t input_length,
                       const char *delimiter_pattern,
                       char ***parts_out, size_t *count_out)
{
    regex_t regex;
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    int status = SPLIT_SUCCESS;
    int regex_status;

    if (input == NULL || delimiter_pattern == NULL ||
        parts_out == NULL || count_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *parts_out = NULL;
    *count_out = 0;

    regex_status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (regex_status != 0) {
        return SPLIT_REGEX_ERROR;
    }

    while (offset <= input_length) {
        regmatch_t match;
        const char *cursor = input + offset;
        const size_t remaining = input_length - offset;
        const int execution_flags = offset == 0 ? 0 : REG_NOTBOL;

        regex_status = regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_status == REG_NOMATCH) {
            status = append_part(&parts, &count, &capacity,
                                 cursor, remaining);
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 ||
            match.rm_eo < match.rm_so) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        {
            const uintmax_t raw_start = (uintmax_t)match.rm_so;
            const uintmax_t raw_end = (uintmax_t)match.rm_eo;

            if (raw_start > SIZE_MAX || raw_end > SIZE_MAX) {
                status = SPLIT_REGEX_ERROR;
                break;
            }

            const size_t match_start = (size_t)raw_start;
            const size_t match_end = (size_t)raw_end;

            if (match_start > remaining || match_end > remaining) {
                status = SPLIT_REGEX_ERROR;
                break;
            }

            if (match_start == match_end) {
                status = SPLIT_EMPTY_DELIMITER_MATCH;
                break;
            }

            status = append_part(&parts, &count, &capacity,
                                 cursor, match_start);
            if (status != SPLIT_SUCCESS) {
                break;
            }

            offset += match_end;
        }
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

int main(int argc, char * const argv[])
{
    char **parts = NULL;
    size_t count = 0;
    int output_failed = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    {
        const size_t input_length = strlen(argv[2]);
        const int status = split_regex(argv[2], input_length, argv[1],
                                       &parts, &count);

        if (status != SPLIT_SUCCESS) {
            fprintf(stderr, "Split failed: %s\n",
                    split_status_message(status));
            return EXIT_FAILURE;
        }
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