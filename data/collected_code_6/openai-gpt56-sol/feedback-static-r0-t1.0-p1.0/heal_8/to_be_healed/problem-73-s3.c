#include <errno.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int append_token(char ***tokens, size_t *count, size_t *capacity,
                        const char *start, size_t length)
{
    char *token;

    if (tokens == NULL || count == NULL || capacity == NULL ||
        start == NULL || *count > *capacity) {
        return EINVAL;
    }

    if (length == SIZE_MAX) {
        return EOVERFLOW;
    }

    token = malloc(length + 1);
    if (token == NULL) {
        return ENOMEM;
    }

    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, start, length);
    }
    token[length] = '\0';

    if (*count == *capacity) {
        char **resized;
        size_t new_capacity;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                free(token);
                return EOVERFLOW;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof(**tokens)) {
            free(token);
            return EOVERFLOW;
        }

        resized = realloc(*tokens, new_capacity * sizeof(**tokens));
        if (resized == NULL) {
            free(token);
            return ENOMEM;
        }

        *tokens = resized;
        *capacity = new_capacity;
    }

    (*tokens)[*count] = token;
    ++(*count);

    return 0;
}

static int split_regex_n(const char *input, size_t input_length,
                         const char *delimiter_pattern,
                         char ***result, size_t *result_count)
{
    regex_t regex;
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    int regex_status;
    int status = 0;

    if (input == NULL || delimiter_pattern == NULL ||
        result == NULL || result_count == NULL) {
        return EINVAL;
    }

    *result = NULL;
    *result_count = 0;

    if (input_length == SIZE_MAX ||
        memchr(input, '\0', input_length) != NULL ||
        input[input_length] != '\0') {
        return EINVAL;
    }

    regex_status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (regex_status != 0) {
        return EINVAL;
    }

    while (offset <= input_length) {
        regmatch_t match;
        size_t remaining = input_length - offset;
        size_t match_start;
        size_t match_end;

        regex_status = regexec(&regex, input + offset, 1, &match, 0);

        if (regex_status == REG_NOMATCH) {
            status = append_token(&tokens, &count, &capacity,
                                  input + offset, remaining);
            break;
        }

        if (regex_status != 0 || match.rm_so < 0 || match.rm_eo < 0) {
            status = EINVAL;
            break;
        }

        if ((uintmax_t)match.rm_so > (uintmax_t)SIZE_MAX ||
            (uintmax_t)match.rm_eo > (uintmax_t)SIZE_MAX) {
            status = EOVERFLOW;
            break;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start > match_end || match_end > remaining) {
            status = EINVAL;
            break;
        }

        if (match_start == match_end) {
            status = EINVAL;
            break;
        }

        status = append_token(&tokens, &count, &capacity,
                              input + offset, match_start);
        if (status != 0) {
            break;
        }

        if (match_end > input_length - offset) {
            status = EOVERFLOW;
            break;
        }

        offset += match_end;
    }

    regfree(&regex);

    if (status != 0) {
        free_tokens(tokens, count);
        return status;
    }

    *result = tokens;
    *result_count = count;
    return 0;
}

int main(void)
{
    static const char input[] = "alpha,beta;gamma delta|epsilon";
    static const char delimiters[] = "[,;|[:space:]]+";
    char **tokens = NULL;
    size_t count = 0;
    size_t i;
    int status;

    status = split_regex_n(input, sizeof(input) - 1,
                           delimiters, &tokens, &count);
    if (status != 0) {
        fprintf(stderr, "Failed to split string: %s\n", strerror(status));
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (printf("%s\n", tokens[i]) < 0) {
            free_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, count);

    if (fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}