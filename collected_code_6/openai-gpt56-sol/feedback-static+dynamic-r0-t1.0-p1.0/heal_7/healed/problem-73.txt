#include <stdint.h>
#include <regex.h>
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
    char *token;

    if (tokens == NULL || count == NULL || capacity == NULL ||
        start == NULL || length == SIZE_MAX) {
        return -1;
    }

    if (*count > *capacity || (*capacity != 0 && *tokens == NULL)) {
        return -1;
    }

    if (*count == *capacity) {
        size_t new_capacity;
        char **resized;

        if (*capacity == 0) {
            new_capacity = 8;
        } else {
            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }
            new_capacity = *capacity * 2;
        }

        if (new_capacity > SIZE_MAX / sizeof **tokens) {
            return -1;
        }

        resized = realloc(*tokens, new_capacity * sizeof **tokens);
        if (resized == NULL) {
            return -1;
        }

        *tokens = resized;
        *capacity = new_capacity;
    }

    token = malloc(length + 1);
    if (token == NULL) {
        return -1;
    }

    if (length > 0) {
        memmove(token, start, length);
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
    char *buffer = NULL;
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t offset = 0;
    int status;

    if (result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    if (input == NULL || delimiter_pattern == NULL ||
        input_length == SIZE_MAX ||
        input_length > (size_t)INTPTR_MAX) {
        return -1;
    }

    buffer = malloc(input_length + 1);
    if (buffer == NULL) {
        return -1;
    }

    if (input_length > 0) {
        memmove(buffer, input, input_length);
    }
    buffer[input_length] = '\0';

    status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (status != 0) {
        free(buffer);
        return -1;
    }

    while (offset < input_length) {
        regmatch_t match;
        size_t remaining = input_length - offset;
        size_t match_start;
        size_t match_end;
        int flags = offset == 0 ? 0 : REG_NOTBOL;

        status = regexec(&regex, buffer + offset, 1, &match, flags);

        if (status == REG_NOMATCH) {
            if (add_token(&tokens, &count, &capacity,
                          buffer + offset, remaining) != 0) {
                goto fail;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0) {
            goto fail;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_end <= match_start || match_end > remaining) {
            goto fail;
        }

        if (match_start > 0 &&
            add_token(&tokens, &count, &capacity,
                      buffer + offset, match_start) != 0) {
            goto fail;
        }

        offset += match_end;
    }

    regfree(&regex);
    free(buffer);
    *result = tokens;
    *result_count = count;
    return 0;

fail:
    regfree(&regex);
    free(buffer);
    free_tokens(tokens, count);
    return -1;
}

int main(void)
{
    static const char input[] = "alpha,beta;gamma|delta  epsilon";
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