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
    size_t i;

    if (tokens == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(tokens[i]);
    }

    free(tokens);
}

static SplitStatus append_token(
    char ***tokens,
    size_t *count,
    size_t *capacity,
    const char *start,
    size_t length)
{
    char **resized_tokens;
    char *token;
    size_t maximum_capacity;
    size_t new_capacity;

    if (length == SIZE_MAX) {
        return SPLIT_OVERFLOW_ERROR;
    }

    if (*count == *capacity) {
        maximum_capacity = SIZE_MAX / sizeof(**tokens);

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

        resized_tokens = realloc(*tokens, new_capacity * sizeof(**tokens));
        if (resized_tokens == NULL) {
            return SPLIT_MEMORY_ERROR;
        }

        *tokens = resized_tokens;
        *capacity = new_capacity;
    }

    token = malloc(length + 1);
    if (token == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    if (length > 0) {
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
    regex_t regex;
    regmatch_t match;
    char **tokens = NULL;
    const char *cursor;
    size_t count = 0;
    size_t capacity = 0;
    size_t remaining;
    size_t match_start;
    size_t match_end;
    int regex_result;
    int execution_flags = 0;
    SplitStatus status;

    if (input == NULL || delimiter_pattern == NULL ||
        output_tokens == NULL || output_count == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *output_tokens = NULL;
    *output_count = 0;

    regex_result = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (regex_result != 0) {
        return SPLIT_REGEX_ERROR;
    }

    cursor = input;
    remaining = strlen(input);

    for (;;) {
        regex_result = regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_result == REG_NOMATCH) {
            status = append_token(
                &tokens, &count, &capacity, cursor, remaining);
            if (status != SPLIT_SUCCESS) {
                free_tokens(tokens, count);
                regfree(&regex);
                return status;
            }
            break;
        }

        if (regex_result != 0 || match.rm_so < 0 || match.rm_eo < match.rm_so) {
            free_tokens(tokens, count);
            regfree(&regex);
            return SPLIT_REGEX_ERROR;
        }

        if ((uintmax_t)match.rm_so > (uintmax_t)remaining ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            free_tokens(tokens, count);
            regfree(&regex);
            return SPLIT_REGEX_ERROR;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start == match_end) {
            free_tokens(tokens, count);
            regfree(&regex);
            return SPLIT_ZERO_LENGTH_DELIMITER;
        }

        status = append_token(
            &tokens, &count, &capacity, cursor, match_start);
        if (status != SPLIT_SUCCESS) {
            free_tokens(tokens, count);
            regfree(&regex);
            return status;
        }

        cursor += match_end;
        remaining -= match_end;
        execution_flags = REG_NOTBOL;
    }

    regfree(&regex);
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
    char **tokens = NULL;
    size_t token_count = 0;
    size_t i;
    SplitStatus status;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <delimiter-regex> <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    status = split_regex(argv[2], argv[1], &tokens, &token_count);
    if (status != SPLIT_SUCCESS) {
        fprintf(stderr, "Split failed: %s\n", split_status_message(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < token_count; ++i) {
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