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

static int append_part(char ***parts, size_t *count, size_t *capacity,
                       const char *start, size_t length)
{
    if (parts == NULL || count == NULL || capacity == NULL || start == NULL) {
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
        size_t new_capacity;

        if (*capacity >= maximum_capacity) {
            free(part);
            return SPLIT_MEMORY_ERROR;
        }

        if (*capacity == 0) {
            new_capacity = maximum_capacity < 8 ? maximum_capacity : 8;
        } else if (*capacity > maximum_capacity - (*capacity / 2 + 1)) {
            new_capacity = maximum_capacity;
        } else {
            new_capacity = *capacity + *capacity / 2 + 1;
        }

        char **resized = realloc(*parts, new_capacity * sizeof **parts);
        if (resized == NULL) {
            free(part);
            return SPLIT_MEMORY_ERROR;
        }

        *parts = resized;
        *capacity = new_capacity;
    }

    (*parts)[*count] = part;
    ++(*count);

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
    int regex_status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (regex_status != 0) {
        return SPLIT_REGEX_ERROR;
    }

    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    const size_t input_length = strlen(input);
    const char *cursor = input;
    int status = SPLIT_SUCCESS;

    for (;;) {
        regmatch_t match;
        const int execution_flags = offset == 0 ? 0 : REG_NOTBOL;

        regex_status = regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_status == REG_NOMATCH) {
            status = append_part(&parts, &count, &capacity, cursor,
                                 input_length - offset);
            break;
        }

        if (regex_status != 0 ||
            match.rm_so < 0 ||
            match.rm_eo < 0 ||
            match.rm_eo < match.rm_so) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        if (match.rm_so == match.rm_eo) {
            status = SPLIT_EMPTY_DELIMITER_MATCH;
            break;
        }

        if ((uintmax_t)match.rm_so > SIZE_MAX ||
            (uintmax_t)match.rm_eo > SIZE_MAX) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        const size_t match_start = (size_t)match.rm_so;
        const size_t match_end = (size_t)match.rm_eo;
        const size_t remaining = input_length - offset;

        if (match_start > remaining || match_end > remaining) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        status = append_part(&parts, &count, &capacity, cursor, match_start);
        if (status != SPLIT_SUCCESS) {
            break;
        }

        cursor += match_end;
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

int main(int argc, char *const argv[])
{
    if (argc != 3) {
        const char *program_name =
            argc > 0 && argv != NULL && argv[0] != NULL
                ? argv[0]
                : "split";

        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n",
                program_name);
        return EXIT_FAILURE;
    }

    char **parts = NULL;
    size_t count = 0;

    const int status = split_regex(argv[2], argv[1], &parts, &count);
    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Split failed: %s\n", split_status_message(status));
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
        fputs("Output failed\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}