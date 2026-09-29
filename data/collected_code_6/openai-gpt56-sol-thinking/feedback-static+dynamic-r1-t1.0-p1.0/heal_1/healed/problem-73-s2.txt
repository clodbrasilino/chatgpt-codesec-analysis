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
    if (tokens == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
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
    char *token;

    if (tokens == NULL || count == NULL || capacity == NULL ||
        (start == NULL && length != 0)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_OVERFLOW_ERROR;
    }

    if (*count == *capacity) {
        const size_t maximum_capacity = SIZE_MAX / sizeof **tokens;
        size_t new_capacity;
        char **resized_tokens;

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

        if (new_capacity <= *capacity) {
            return SPLIT_OVERFLOW_ERROR;
        }

        resized_tokens = realloc(
            *tokens, new_capacity * sizeof *resized_tokens);
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

    if (length != 0) {
        memcpy(token, start, length);
    }
    token[length] = '\0';

    (*tokens)[*count] = token;
    ++*count;

    return SPLIT_SUCCESS;
}

static SplitStatus split_regex(
    const char *input,
    const char *delimiter_pattern,
    char ***output_tokens,
    size_t *output_count)
{
    regex_t regex;
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t remaining;
    const char *cursor;
    int execution_flags = 0;
    int regex_result;
    SplitStatus status = SPLIT_SUCCESS;

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
        regmatch_t match;

        regex_result = regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_result == REG_NOMATCH) {
            status = append_token(
                &tokens, &count, &capacity, cursor, remaining);
            break;
        }

        if (regex_result != 0) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        if ((uintmax_t)match.rm_so > (uintmax_t)remaining ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        {
            const size_t match_start = (size_t)match.rm_so;
            const size_t match_end = (size_t)match.rm_eo;

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
    char **tokens = NULL;
    size_t token_count = 0;
    SplitStatus status;
    const char *program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "split";

    if (argc != 3) {
        fprintf(
            stderr,
            "Usage: %s <delimiter-regex> <string>\n",
            program_name);
        return EXIT_FAILURE;
    }

    status = split_regex(argv[2], argv[1], &tokens, &token_count);
    if (status != SPLIT_SUCCESS) {
        fprintf(
            stderr,
            "Split failed: %s\n",
            split_status_message(status));
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