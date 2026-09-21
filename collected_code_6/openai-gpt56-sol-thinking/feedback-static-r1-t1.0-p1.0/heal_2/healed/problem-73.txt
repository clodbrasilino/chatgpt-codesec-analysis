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

static int regoff_to_size(regoff_t value, size_t *result)
{
    if (result == NULL || value < 0) {
        return 0;
    }

    const uintmax_t converted = (uintmax_t)value;

    if (converted > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *result = (size_t)converted;
    return 1;
}

static int append_part(char ***parts, size_t *count, size_t *capacity,
                       const char *start, size_t length)
{
    if (parts == NULL || count == NULL || capacity == NULL || start == NULL ||
        *count > *capacity ||
        ((*parts == NULL) != (*capacity == 0))) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_MEMORY_ERROR;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    memcpy(part, start, length);
    part[length] = '\0';

    if (*count == *capacity) {
        const size_t maximum_capacity = SIZE_MAX / sizeof **parts;

        if (*count >= maximum_capacity) {
            free(part);
            return SPLIT_MEMORY_ERROR;
        }

        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = maximum_capacity < 8 ? maximum_capacity : 8;
        } else {
            const size_t growth = *capacity / 2 + 1;

            if (*capacity > maximum_capacity - growth) {
                new_capacity = maximum_capacity;
            } else {
                new_capacity = *capacity + growth;
            }
        }

        char **resized = realloc(*parts, new_capacity * sizeof *resized);
        if (resized == NULL) {
            free(part);
            return SPLIT_MEMORY_ERROR;
        }

        *parts = resized;
        *capacity = new_capacity;
    }

    (*parts)[*count] = part;
    ++*count;

    return SPLIT_SUCCESS;
}

static int split_regex(const char *input, const char *delimiter_pattern,
                       char ***parts_out, size_t *count_out)
{
    if (input == NULL || delimiter_pattern == NULL ||
        parts_out == NULL || count_out == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *parts_out = NULL;
    *count_out = 0;

    regex_t regex;
    if (regcomp(&regex, delimiter_pattern, REG_EXTENDED) != 0) {
        return SPLIT_REGEX_ERROR;
    }

    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    const size_t input_length = strlen(input);
    int status = SPLIT_SUCCESS;

    for (;;) {
        if (offset > input_length) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        const char *cursor = input + offset;
        const size_t remaining = input_length - offset;
        regmatch_t match;
        const int execution_flags = offset == 0 ? 0 : REG_NOTBOL;
        const int regex_status =
            regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_status == REG_NOMATCH) {
            status = append_part(&parts, &count, &capacity,
                                 cursor, remaining);
            break;
        }

        if (regex_status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo < 0) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        if (match.rm_so == match.rm_eo) {
            status = SPLIT_EMPTY_DELIMITER_MATCH;
            break;
        }

        if (match.rm_so > match.rm_eo) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        size_t match_start;
        size_t match_end;

        if (!regoff_to_size(match.rm_so, &match_start) ||
            !regoff_to_size(match.rm_eo, &match_end) ||
            match_start > remaining ||
            match_end > remaining) {
            status = SPLIT_REGEX_ERROR;
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

int main(int argc, char *argv[const])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *delimiter_pattern = argv[1];
    const char *input = argv[2];
    char **parts = NULL;
    size_t count = 0;

    const int status =
        split_regex(input, delimiter_pattern, &parts, &count);

    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Split failed: %s\n",
                split_status_message(status));
        return EXIT_FAILURE;
    }

    int output_failed = 0;

    for (size_t i = 0; i < count; ++i) {
        if (printf("%s\n", parts[i]) < 0) {
            output_failed = 1;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        output_failed = 1;
    }

    free_split_result(parts, count);

    if (output_failed) {
        fprintf(stderr, "Output failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}