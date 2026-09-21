#include <limits.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int add_token(char ***tokens, size_t *count, size_t *capacity,
                     const char *start, size_t length)
{
    if (tokens == NULL || count == NULL || capacity == NULL ||
        (start == NULL && length != 0) || *count > *capacity ||
        *count == SIZE_MAX || length == SIZE_MAX) {
        return -1;
    }

    if (*count == *capacity) {
        size_t new_capacity = *capacity == 0 ? 8 : *capacity;

        if (*capacity != 0) {
            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity <= *count ||
            new_capacity > SIZE_MAX / sizeof **tokens) {
            return -1;
        }

        char **resized = realloc(*tokens,
                                 new_capacity * sizeof **tokens);
        if (resized == NULL) {
            return -1;
        }

        *tokens = resized;
        *capacity = new_capacity;
    }

    char *token = malloc(length + 1);
    if (token == NULL) {
        return -1;
    }

    if (length != 0) {
        memcpy(token, start, length);
    }
    token[length] = '\0';

    (*tokens)[*count] = token;
    ++*count;

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

    if (input == NULL || delimiter_pattern == NULL ||
        result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (input_length > (size_t)PTRDIFF_MAX ||
        memchr(input, '\0', input_length) != NULL ||
        input[input_length] != '\0') {
        return -1;
    }

    if (regcomp(&regex, delimiter_pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    while (offset < input_length) {
        size_t remaining = input_length - offset;
        regmatch_t match;
        int status = regexec(&regex, input + offset, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (add_token(&tokens, &count, &capacity,
                          input + offset, remaining) != 0) {
                goto fail;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0 ||
            match.rm_eo <= match.rm_so) {
            goto fail;
        }

        uintmax_t raw_start = (uintmax_t)match.rm_so;
        uintmax_t raw_end = (uintmax_t)match.rm_eo;

        if (raw_start > SIZE_MAX || raw_end > SIZE_MAX) {
            goto fail;
        }

        size_t match_start = (size_t)raw_start;
        size_t match_end = (size_t)raw_end;

        if (match_start >= match_end || match_end > remaining) {
            goto fail;
        }

        if (match_start != 0 &&
            add_token(&tokens, &count, &capacity,
                      input + offset, match_start) != 0) {
            goto fail;
        }

        offset += match_end;
    }

    regfree(&regex);
    *result = tokens;
    *result_count = count;
    return 0;

fail:
    regfree(&regex);
    free_tokens(tokens, count);
    return -1;
}

int main(void)
{
    static const char input[] =
        "alpha,beta;gamma|delta  epsilon";
    static const char delimiters[] = "[,;|[:space:]]+";
    char **tokens = NULL;
    size_t count = 0;

    if (split_regex_n(input, sizeof input - 1, delimiters,
                      &tokens, &count) != 0) {
        fputs("Failed to split input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; ++i) {
        if (printf("%s\n", tokens[i]) < 0) {
            free_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}