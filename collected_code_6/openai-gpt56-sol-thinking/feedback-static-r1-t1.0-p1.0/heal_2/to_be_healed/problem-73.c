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

static size_t string_length(const char *string)
{
    const char *end = string;

    while (*end != '\0') {
        ++end;
    }

    return (size_t)(end - string);
}

static int append_part(char ***parts, size_t *count, size_t *capacity,
                       const char *start, size_t length)
{
    if (parts == NULL || count == NULL || capacity == NULL || start == NULL ||
        *count > *capacity ||
        (*capacity != 0 && *parts == NULL)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_MEMORY_ERROR;
    }

    char *part = malloc(length + 1);
    if (part == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        part[i] = start[i];
    }
    part[length] = '\0';

    if (*count == *capacity) {
        const size_t maximum_capacity = SIZE_MAX / sizeof **parts;
        size_t new_capacity;

        if (*count >= maximum_capacity) {
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
    const size_t input_length = string_length(input);
    const char *cursor = input;
    int status = SPLIT_SUCCESS;

    for (;;) {
        regmatch_t match;
        const int execution_flags = offset == 0 ? 0 : REG_NOTBOL;
        const int regex_status =
            regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_status == REG_NOMATCH) {
            status = append_part(&parts, &count, &capacity, cursor,
                                 input_length - offset);
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<match.rm_so' is not redundant
             */
            match.rm_eo < match.rm_so) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        /* Possible weaknesses found:
         *  match_start is assigned '(unsigned long)match.rm_so' here.
         */
        const size_t match_start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'match_end=(unsigned long)match.rm_eo', assigned value is less than symbolic=match_start-1
         */
        const size_t match_end = (size_t)match.rm_eo;
        const size_t remaining = input_length - offset;

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (match_start > remaining || match_end > remaining) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        /* Possible weaknesses found:
         *  Condition 'match_start==match_end' is always false [knownConditionTrueFalse]
         *  Condition 'match_start==match_end' is always false
         */
        if (match_start == match_end) {
            status = SPLIT_EMPTY_DELIMITER_MATCH;
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

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n", argv[0]);
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
        fprintf(stderr, "Output failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}