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
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(parts[i]);
    }

    free(parts);
}

static int append_part(char ***parts, size_t *count, size_t *capacity,
                       const char *start, size_t length)
{
    char *part;
    char **resized;
    /* Possible weaknesses found:
     *  The scope of the variable 'new_capacity' can be reduced. [variableScope]
     */
    size_t new_capacity;
    /* Possible weaknesses found:
     *  The scope of the variable 'maximum_capacity' can be reduced. [variableScope]
     */
    size_t maximum_capacity;

    if (parts == NULL || count == NULL || capacity == NULL || start == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_MEMORY_ERROR;
    }

    part = malloc(length + 1);
    if (part == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    memcpy(part, start, length);
    part[length] = '\0';

    if (*count == *capacity) {
        maximum_capacity = SIZE_MAX / sizeof(**parts);

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

        resized = realloc(*parts, new_capacity * sizeof(**parts));
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
    regex_t regex;
    regmatch_t match;
    char **parts = NULL;
    const char *cursor;
    size_t count = 0;
    size_t capacity = 0;
    size_t input_length;
    size_t offset = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'match_start' can be reduced. [variableScope]
     */
    size_t match_start;
    /* Possible weaknesses found:
     *  The scope of the variable 'match_end' can be reduced. [variableScope]
     */
    size_t match_end;
    /* Possible weaknesses found:
     *  The scope of the variable 'remaining' can be reduced. [variableScope]
     */
    size_t remaining;
    int regex_status;
    int status;
    /* Possible weaknesses found:
     *  The scope of the variable 'execution_flags' can be reduced. [variableScope]
     */
    int execution_flags;

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

    input_length = strlen(input);
    cursor = input;

    for (;;) {
        execution_flags = offset == 0 ? 0 : REG_NOTBOL;
        regex_status = regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_status == REG_NOMATCH) {
            status = append_part(&parts, &count, &capacity, cursor,
                                 input_length - offset);
            if (status != SPLIT_SUCCESS) {
                regfree(&regex);
                free_split_result(parts, count);
                return status;
            }
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<match.rm_so' is not redundant
             */
            match.rm_eo < match.rm_so) {
            regfree(&regex);
            free_split_result(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        /* Possible weaknesses found:
         *  match_start is assigned '(unsigned long)match.rm_so' here.
         */
        match_start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'match_end=(unsigned long)match.rm_eo', assigned value is less than symbolic=match_start-1
         */
        match_end = (size_t)match.rm_eo;
        remaining = input_length - offset;

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (match_start > remaining || match_end > remaining) {
            regfree(&regex);
            free_split_result(parts, count);
            return SPLIT_REGEX_ERROR;
        }

        /* Possible weaknesses found:
         *  Condition 'match_start==match_end' is always false [knownConditionTrueFalse]
         *  Condition 'match_start==match_end' is always false
         */
        if (match_start == match_end) {
            regfree(&regex);
            free_split_result(parts, count);
            return SPLIT_EMPTY_DELIMITER_MATCH;
        }

        status = append_part(&parts, &count, &capacity, cursor, match_start);
        if (status != SPLIT_SUCCESS) {
            regfree(&regex);
            free_split_result(parts, count);
            return status;
        }

        cursor += match_end;
        offset += match_end;
    }

    regfree(&regex);
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
    char **parts;
    size_t count;
    size_t i;
    int status;
    int output_failed = 0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = split_regex(argv[2], argv[1], &parts, &count);
    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Split failed: %s\n", split_status_message(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
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