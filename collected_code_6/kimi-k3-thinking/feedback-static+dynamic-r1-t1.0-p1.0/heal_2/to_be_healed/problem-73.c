#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_STR_LEN ((size_t)16 * 1024 * 1024)
#define MAX_DELIMS_LEN ((size_t)1024)

typedef struct {
    char **tokens;
    size_t count;
} split_result_t;

static char *build_pattern(const char *delims, size_t delims_len)
{
    size_t pos = 0;
    size_t i;
    char *pattern;

    if (delims == NULL || delims_len == 0 || delims_len > MAX_DELIMS_LEN) {
        return NULL;
    }

    if (delims_len > SIZE_MAX - 4) {
        return NULL;
    }

    pattern = malloc(delims_len + 4);
    if (pattern == NULL) {
        return NULL;
    }

    pattern[pos++] = '[';
    if (memchr(delims, ']', delims_len) != NULL) {
        pattern[pos++] = ']';
    }
    for (i = 0; i < delims_len; i++) {
        char c = delims[i];
        if (c == ']' || c == '-' || c == '^') {
            continue;
        }
        pattern[pos++] = c;
    }
    if (memchr(delims, '^', delims_len) != NULL) {
        pattern[pos++] = '^';
    }
    if (memchr(delims, '-', delims_len) != NULL) {
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
    size_t alloc_size;

    if (tokens == NULL || count == NULL || capacity == NULL ||
        start == NULL || len == 0 || len > MAX_STR_LEN) {
        return -1;
    }

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

    if (len >= SIZE_MAX) {
        return -1;
    }
    /* Possible weaknesses found:
     *  alloc_size is assigned 'len+1' here.
     */
    alloc_size = len + 1;

    token = malloc(alloc_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (token == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition 'len>=alloc_size' is always false
     *  Condition 'len>=alloc_size' is always false [knownConditionTrueFalse]
     */
    if (len >= alloc_size) {
        free(token);
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
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
    char *pattern = NULL;
    char *input_copy = NULL;
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    size_t i;
    size_t str_len;
    size_t delims_len;
    const char *cursor;
    const char *end;
    int exec_status;
    int regex_ready = 0;
    int ret = -1;

    if (str == NULL || delims == NULL || result == NULL) {
        return -1;
    }

    result->tokens = NULL;
    result->count = 0;

    delims_len = strnlen(delims, MAX_DELIMS_LEN + 1);
    if (delims_len == 0 || delims_len > MAX_DELIMS_LEN) {
        return -1;
    }

    str_len = strnlen(str, MAX_STR_LEN + 1);
    if (str_len > MAX_STR_LEN) {
        return -1;
    }

    input_copy = malloc(str_len + 1);
    if (input_copy == NULL) {
        return -1;
    }
    if (str_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(input_copy, str, str_len);
    }
    input_copy[str_len] = '\0';

    pattern = build_pattern(delims, delims_len);
    if (pattern == NULL) {
        goto cleanup;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        goto cleanup;
    }
    regex_ready = 1;
    free(pattern);
    pattern = NULL;

    cursor = input_copy;
    end = input_copy + str_len;

    while (cursor < end) {
        size_t token_len;
        size_t remaining = (size_t)(end - cursor);

        exec_status = regexec(&regex, cursor, 1, &match, 0);
        if (exec_status == REG_NOMATCH) {
            break;
        }
        if (exec_status != 0) {
            goto cleanup;
        }

        if (match.rm_so < 0 || match.rm_eo <= 0 || match.rm_eo < match.rm_so) {
            goto cleanup;
        }
        if ((uintmax_t)match.rm_eo > (uintmax_t)remaining) {
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

    if (cursor < end) {
        if (add_token(&tokens, &count, &capacity, cursor,
                      (size_t)(end - cursor)) != 0) {
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
    if (regex_ready) {
        regfree(&regex);
    }
    free(pattern);
    free(input_copy);

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