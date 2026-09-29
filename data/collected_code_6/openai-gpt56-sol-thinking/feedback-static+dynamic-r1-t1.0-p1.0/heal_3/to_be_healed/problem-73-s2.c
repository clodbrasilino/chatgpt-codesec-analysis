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

static SplitStatus get_string_length(const char *string, size_t *length)
{
    size_t result = 0;

    if (string == NULL || length == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    while (string[result] != '\0') {
        if (result == SIZE_MAX - 1) {
            return SPLIT_OVERFLOW_ERROR;
        }

        ++result;
    }

    *length = result;
    return SPLIT_SUCCESS;
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
        (start == NULL && length != 0) || *count > *capacity ||
        (*capacity != 0 && *tokens == NULL)) {
        return SPLIT_INVALID_ARGUMENT;
    }

    if (length == SIZE_MAX) {
        return SPLIT_OVERFLOW_ERROR;
    }

    token = malloc(length + 1);
    if (token == NULL) {
        return SPLIT_MEMORY_ERROR;
    }

    for (size_t i = 0; i < length; ++i) {
        token[i] = start[i];
    }

    token[length] = '\0';

    if (*count == *capacity) {
        const size_t maximum_capacity = SIZE_MAX / sizeof **tokens;
        size_t new_capacity;
        char **resized_tokens;

        if (*capacity >= maximum_capacity) {
            free(token);
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
            free(token);
            return SPLIT_OVERFLOW_ERROR;
        }

        resized_tokens = realloc(
            *tokens, new_capacity * sizeof *resized_tokens);
        if (resized_tokens == NULL) {
            free(token);
            return SPLIT_MEMORY_ERROR;
        }

        *tokens = resized_tokens;
        *capacity = new_capacity;
    }

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
    size_t remaining = 0;
    const char *cursor;
    int execution_flags = 0;
    int regex_result;
    SplitStatus status;

    if (output_tokens == NULL || output_count == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    *output_tokens = NULL;
    *output_count = 0;

    if (input == NULL || delimiter_pattern == NULL) {
        return SPLIT_INVALID_ARGUMENT;
    }

    status = get_string_length(input, &remaining);
    if (status != SPLIT_SUCCESS) {
        return status;
    }

    regex_result = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (regex_result != 0) {
        return SPLIT_REGEX_ERROR;
    }

    cursor = input;
    /* Possible weaknesses found:
     *  Value stored to 'status' is never read [deadcode.DeadStores]
     */
    status = SPLIT_SUCCESS;

    for (;;) {
        regmatch_t match;
        size_t match_start;
        size_t match_end;

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

        if (match.rm_so < 0 || match.rm_eo < 0 ||
            match.rm_eo < match.rm_so) {
            status = SPLIT_REGEX_ERROR;
            break;
        }

        if (match.rm_so == match.rm_eo) {
            status = SPLIT_ZERO_LENGTH_DELIMITER;
            break;
        }

        if ((uintmax_t)match.rm_so > (uintmax_t)SIZE_MAX ||
            (uintmax_t)match.rm_eo > (uintmax_t)SIZE_MAX) {
            status = SPLIT_OVERFLOW_ERROR;
            break;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start > remaining || match_end > remaining) {
            status = SPLIT_REGEX_ERROR;
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
    char **tokens = NULL;
    size_t token_count = 0;
    SplitStatus status;
    const char *program_name =
        argc > 0 && argv != NULL && argv[0] != NULL ? argv[0] : "split";

    if (argc != 3 || argv == NULL || argv[1] == NULL || argv[2] == NULL) {
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