#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

typedef struct {
    char **tokens;
    size_t count;
} split_result_t;

static char *build_pattern(const char *delims)
{
    size_t len = strlen(delims);
    size_t pos = 0;
    size_t i;
    char *pattern = malloc(len + 4);

    if (pattern == NULL) {
        return NULL;
    }

    pattern[pos++] = '[';
    if (strchr(delims, ']') != NULL) {
        pattern[pos++] = ']';
    }
    for (i = 0; i < len; i++) {
        char c = delims[i];
        if (c == ']' || c == '-' || c == '^') {
            continue;
        }
        pattern[pos++] = c;
    }
    if (strchr(delims, '^') != NULL) {
        pattern[pos++] = '^';
    }
    if (strchr(delims, '-') != NULL) {
        pattern[pos++] = '-';
    }
    pattern[pos++] = ']';
    pattern[pos++] = '+';
    pattern[pos] = '\0';

    return pattern;
}

static int add_token(char ***tokens, size_t *count, size_t *capacity,
                     const char *start, size_t len)
{
    char *token;

    if (*count == *capacity) {
        size_t new_capacity;
        char **new_tokens;

        if (*capacity > SIZE_MAX / (2 * sizeof(**tokens))) {
            return -1;
        }
        new_capacity = (*capacity == 0) ? 8 : *capacity * 2;
        new_tokens = realloc(*tokens, new_capacity * sizeof(*new_tokens));
        if (new_tokens == NULL) {
            return -1;
        }
        *tokens = new_tokens;
        *capacity = new_capacity;
    }

    token = malloc(len + 1);
    if (token == NULL) {
        return -1;
    }
    memcpy(token, start, len);
    token[len] = '\0';

    (*tokens)[*count] = token;
    (*count)++;

    return 0;
}

static int split_string(const char *str, const char *delims, split_result_t *result)
{
    regex_t regex;
    regmatch_t match;
    char *pattern;
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i;
    const char *cursor;
    int exec_status;
    int ret = -1;

    if (str == NULL || delims == NULL || *delims == '\0' || result == NULL) {
        return -1;
    }

    result->tokens = NULL;
    result->count = 0;

    pattern = build_pattern(delims);
    if (pattern == NULL) {
        return -1;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(pattern);
        return -1;
    }
    free(pattern);

    cursor = str;
    while (*cursor != '\0') {
        size_t token_len;

        exec_status = regexec(&regex, cursor, 1, &match, 0);
        if (exec_status == REG_NOMATCH) {
            break;
        }
        if (exec_status != 0) {
            goto cleanup;
        }

        token_len = (size_t)match.rm_so;
        if (token_len > 0) {
            if (add_token(&tokens, &count, &capacity, cursor, token_len) != 0) {
                goto cleanup;
            }
        }
        cursor += match.rm_eo;
    }

    if (*cursor != '\0') {
        if (add_token(&tokens, &count, &capacity, cursor, strlen(cursor)) != 0) {
            goto cleanup;
        }
    }

    result->tokens = tokens;
    result->count = count;
    ret = 0;

cleanup:
    if (ret != 0) {
        for (i = 0; i < count; i++) {
            free(tokens[i]);
        }
        free(tokens);
    }
    regfree(&regex);

    return ret;
}

static void free_split_result(split_result_t *result)
{
    size_t i;

    if (result == NULL) {
        return;
    }

    for (i = 0; i < result->count; i++) {
        free(result->tokens[i]);
    }
    free(result->tokens);
    result->tokens = NULL;
    result->count = 0;
}

int main(void)
{
    const char *input = "apple, banana;cherry  grape|orange,,melon";
    const char *delimiters = ",;| ";
    split_result_t result;
    size_t i;

    if (split_string(input, delimiters, &result) != 0) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < result.count; i++) {
        printf("Token %zu: %s\n", i, result.tokens[i]);
    }

    free_split_result(&result);

    return EXIT_SUCCESS;
}