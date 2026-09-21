#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SPLIT_SUCCESS = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_REGEX_ERROR,
    SPLIT_MEMORY_ERROR,
    SPLIT_OVERFLOW_ERROR,
    SPLIT_ZERO_LENGTH_DELIMITER
} SplitStatus;

static void free_tokens(char **tokens, size_t count)
{
    if (tokens != NULL) {
        for (size_t i = 0; i < count; ++i) {
            free(tokens[i]);
        }
        free(tokens);
    }
}

static SplitStatus append_token(
    char ***tokens,
    size_t *count,
    size_t *capacity,
    const char *start,
    size_t length)
{
    if (tokens == NULL || count == NULL || capacity == NULL ||
        (start == NULL && length != 0)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_OVERFLOW_ERROR;
    }

    if (*count == *capacity) {
        const size_t maximum_capacity = SIZE_MAX / sizeof(char *);
        size_t new_capacity;

        if (*capacity >= maximum_capacity) {
            return SPLIT_OVERFLOW_ERROR;
        }

        if (*capacity == 0) {
            new_capacity = maximum_capacity < 8 ? maximum_capacity : 8;
        } else if (*capacity > maximum_capacity / 2) {
            new_capacity = maximum_capacity;
        } else {
            new_capacity = *capacity * 2;
        }

        char **resized_tokens =
            realloc(*tokens, new_capacity * sizeof(*resized_tokens));

        if (resized_tokens == NULL) {
            return SPLIT_MEMORY_ERROR;
        }

        *tokens = resized_tokens;
        *capacity = new_capacity;
    }

    char *token = malloc(length + 1);
    if (token == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, start, length);
    }
    token[length] = '\0';

    (*tokens)[*count] = token;
    ++(*count);

    return SPLIT_SUCCESS;
}

static SplitStatus split_regex(
    const char *input,
    const char *delimiter_pattern,
    char ***output_tokens,
    size_t *output_count)
{
    if (output_tokens == NULL || output_count == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *output_tokens = NULL;
    *output_count = 0;

    if (input == NULL || delimiter_pattern == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    regex_t regex;
    if (regcomp(&regex, delimiter_pattern, REG_EXTENDED) != 0) {
        return SPLIT_REGEX_ERROR;
    }

    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *cursor = input;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t remaining = strlen(input);
    int execution_flags = 0;
    SplitStatus status = SPLIT_SUCCESS;

    for (;;) {
        regmatch_t match;
        int regex_result =
            regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_result == REG_NOMATCH) {
            status = append_token(
                &tokens, &count, &capacity, cursor, remaining);
            break;
        }

        if (regex_result != 0 ||
            match.rm_so < 0 ||
            match.rm_eo < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<match.rm_so' is not redundant
             */
            match.rm_eo < match.rm_so) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if ((uintmax_t)match.rm_so > (uintmax_t)remaining ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
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

        /* Possible weaknesses found:
         *  Condition 'match_start==match_end' is always false [knownConditionTrueFalse]
         *  Condition 'match_start==match_end' is always false
         */
        if (match_start == match_end) {
            status = SPLIT_ZERO_LENGTH_DELIMITER;
            break;
        }

        status = append_token(
            &tokens, &count, &capacity, cursor, match_start);

        if (status != SPLIT_SUCCESS) {
            break;
        }

        cursor += match_end;
        remaining -= match_end;
        execution_flags = REG_NOTBOL;
    }

    regfree(&regex);

    if (status != SPLIT_SUCCESS) {
        free_tokens(tokens, count);
        return status;
    }

    *output_tokens = tokens;
    *output_count = count;
    return SPLIT_SUCCESS;
}

static const char *split_status_message(SplitStatus status)
{
    switch (status) {
        case SPLIT_SUCCESS:
            return "success";
        case SPLIT_INVALID_ARGUMENT:
            return "invalid argument";
        case SPLIT_REGEX_ERROR:
            return "regular expression error";
        case SPLIT_MEMORY_ERROR:
            return "memory allocation error";
        case SPLIT_OVERFLOW_ERROR:
            return "size overflow";
        case SPLIT_ZERO_LENGTH_DELIMITER:
            return "delimiter expression matched an empty string";
        default:
            return "unknown error";
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *delimiter_pattern = argv[1];
    const char *input = argv[2];
    char **tokens = NULL;
    size_t token_count = 0;

    SplitStatus status = split_regex(
        input, delimiter_pattern, &tokens, &token_count);

    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Split failed: %s\n", split_status_message(status));
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < token_count; ++i) {
        if (printf("%s\n", tokens[i]) < 0) {
            free_tokens(tokens, token_count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, token_count);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}