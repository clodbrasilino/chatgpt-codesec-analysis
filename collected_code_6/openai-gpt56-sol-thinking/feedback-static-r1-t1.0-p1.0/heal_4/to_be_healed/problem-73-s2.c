#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    SPLIT_SUCCESS = 0,
    SPLIT_INVALID_ARGUMENT,
    SPLIT_REGEX_ERROR,
    SPLIT_MEMORY_ERROR,
    SPLIT_OVERFLOW_ERROR,
    SPLIT_ZERO_LENGTH_DELIMITER
} SplitStatus;

static size_t string_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
}

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
    if (tokens == NULL ||
        count == NULL ||
        capacity == NULL ||
        (start == NULL && length != 0) ||
        *count > *capacity ||
        (*capacity != 0 && *tokens == NULL)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_OVERFLOW_ERROR;
    }

    if (*count == *capacity) {
        const size_t maximum_capacity = SIZE_MAX / sizeof **tokens;
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

        if (new_capacity <= *capacity) {
            return SPLIT_OVERFLOW_ERROR;
        }

        char **resized_tokens =
            realloc(*tokens, new_capacity * sizeof **tokens);

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

    for (size_t i = 0; i < length; ++i) {
        token[i] = start[i];
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
    size_t remaining = string_length(input);
    int execution_flags = 0;
    SplitStatus status = SPLIT_SUCCESS;

    for (;;) {
        regmatch_t match;
        int regex_result =
            regexec(&regex, cursor, 1, &match, execution_flags);

        if (regex_result == REG_NOMATCH) {
            status = append_token(
                &tokens,
                &count,
                &capacity,
                cursor,
                remaining);
            break;
        }

        if (regex_result != 0 ||
            match.rm_so < 0 ||
            match.rm_eo < 0 ||
            match.rm_eo < match.rm_so) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        uintmax_t start_offset = (uintmax_t)match.rm_so;
        uintmax_t end_offset = (uintmax_t)match.rm_eo;

        if (start_offset > (uintmax_t)remaining ||
            end_offset > (uintmax_t)remaining) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        size_t match_start = (size_t)start_offset;
        size_t match_end = (size_t)end_offset;

        if (match_start == match_end) {
            status = SPLIT_ZERO_LENGTH_DELIMITER;
            break;
        }

        status = append_token(
            &tokens,
            &count,
            &capacity,
            cursor,
            match_start);

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

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[const])
{
    if (argc != 3) {
        fprintf(
            stderr,
            "Usage: %s <delimiter-regex> <string>\n",
            argc > 0 ? argv[0] : "split_regex");
        return EXIT_FAILURE;
    }

    char **tokens = NULL;
    size_t token_count = 0;

    SplitStatus status =
        split_regex(argv[2], argv[1], &tokens, &token_count);

    if (status != SPLIT_SUCCESS) {
        fprintf(
            stderr,
            "Split failed: %s\n",
            split_status_message(status));
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < token_count; ++i) {
        if (fputs(tokens[i], stdout) == EOF ||
            fputc('\n', stdout) == EOF) {
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