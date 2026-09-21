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

    for (size_t i = 0U; i < count; ++i) {
        free(tokens[i]);
    }

    free(tokens);
}

static int add_token(char ***tokens, size_t *count, size_t *capacity,
                     const char *start, size_t length)
{
    char **resized;
    char *token;

    if (length == SIZE_MAX) {
        return -1;
    }

    if (*count == *capacity) {
        size_t new_capacity;

        if (*capacity == 0U) {
            new_capacity = 8U;
        } else {
            if (*capacity > SIZE_MAX / 2U) {
                return -1;
            }
            new_capacity = *capacity * 2U;
        }

        if (new_capacity > SIZE_MAX / sizeof(*resized)) {
            return -1;
        }

        resized = realloc(*tokens, new_capacity * sizeof(*resized));
        if (resized == NULL) {
            return -1;
        }

        *tokens = resized;
        *capacity = new_capacity;
    }

    token = malloc(length + 1U);
    if (token == NULL) {
        return -1;
    }

    if (length != 0U) {
        memcpy(token, start, length);
    }
    token[length] = '\0';

    (*tokens)[*count] = token;
    ++*count;

    return 0;
}

static int split_regex(const char *input, const char *delimiter_pattern,
                       char ***result, size_t *result_count)
{
    regex_t regex;
    char **tokens = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    size_t offset = 0U;
    size_t input_length;
    int status;

    if (input == NULL || delimiter_pattern == NULL ||
        result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0U;
    input_length = strlen(input);

    status = regcomp(&regex, delimiter_pattern, REG_EXTENDED);
    if (status != 0) {
        return -1;
    }

    while (offset < input_length) {
        regmatch_t match;
        size_t remaining = input_length - offset;
        size_t match_start;
        size_t match_end;

        status = regexec(&regex, input + offset, 1U, &match, 0);

        if (status == REG_NOMATCH) {
            if (add_token(&tokens, &count, &capacity,
                          input + offset, remaining) != 0) {
                free_tokens(tokens, count);
                regfree(&regex);
                return -1;
            }
            break;
        }

        if (status != 0 || match.rm_so < 0 || match.rm_eo < 0 ||
            match.rm_eo <= match.rm_so) {
            free_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        match_start = (size_t)match.rm_so;
        match_end = (size_t)match.rm_eo;

        if (match_start > remaining || match_end > remaining) {
            free_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        if (match_start != 0U &&
            add_token(&tokens, &count, &capacity,
                      input + offset, match_start) != 0) {
            free_tokens(tokens, count);
            regfree(&regex);
            return -1;
        }

        offset += match_end;
    }

    regfree(&regex);
    *result = tokens;
    *result_count = count;

    return 0;
}

int main(void)
{
    const char *input = "alpha,beta;gamma|delta  epsilon";
    const char *delimiters = "[,;|[:space:]]+";
    char **tokens = NULL;
    size_t count = 0U;

    if (split_regex(input, delimiters, &tokens, &count) != 0) {
        fputs("Failed to split input\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("%s\n", tokens[i]) < 0) {
            free_tokens(tokens, count);
            return EXIT_FAILURE;
        }
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}