#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define INITIAL_CAPACITY 8

static char *copy_token(const char *start, size_t length)
{
    char *token;
    size_t buffer_size;

    if (start == NULL) {
        return NULL;
    }
    if (length > SIZE_MAX - 1) {
        return NULL;
    }
    buffer_size = length + 1;
    token = malloc(buffer_size);
    if (token == NULL) {
        return NULL;
    }
    if (length > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, start, length);
    }
    token[length] = '\0';
    return token;
}

void free_tokens(char **tokens, size_t count)
{
    size_t i;

    if (tokens == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

char **regex_split(const char *input, size_t input_length, const char *pattern, size_t *token_count)
{
    regex_t regex;
    regmatch_t match[1];
    char **tokens = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *cursor;
    const char *end;
    int status;
    int last;

    if (input == NULL || pattern == NULL || token_count == NULL) {
        return NULL;
    }
    if (input[input_length] != '\0') {
        return NULL;
    }

    *token_count = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    cursor = input;
    end = input + input_length;
    last = 0;

    for (;;) {
        char *token;
        size_t token_length;
        size_t advance = 0;

        if (cursor >= end) {
            token_length = 0;
            last = 1;
        } else {
            status = regexec(&regex, cursor, 1, match, 0);
            if (status == REG_NOMATCH) {
                token_length = (size_t)(end - cursor);
                last = 1;
            } else if (status != 0) {
                free_tokens(tokens, count);
                regfree(&regex);
                return NULL;
            } else {
                if (match[0].rm_so < 0 || match[0].rm_eo < match[0].rm_so ||
                    (size_t)match[0].rm_eo > (size_t)(end - cursor)) {
                    free_tokens(tokens, count);
                    regfree(&regex);
                    return NULL;
                }
                token_length = (size_t)match[0].rm_so;
                advance = (match[0].rm_eo > 0) ? (size_t)match[0].rm_eo : 1;
            }
        }

        if (count == capacity) {
            size_t new_capacity;
            char **new_tokens;

            if (capacity == 0) {
                new_capacity = INITIAL_CAPACITY;
            } else {
                if (capacity > SIZE_MAX / 2) {
                    free_tokens(tokens, count);
                    regfree(&regex);
                    return NULL;
                }
                new_capacity = capacity * 2;
            }
            if (new_capacity > SIZE_MAX / sizeof(*new_tokens)) {
                free_tokens(tokens, count);
                regfree(&regex);
                return NULL;
            }
            new_tokens = realloc(tokens, new_capacity * sizeof(*new_tokens));
            if (new_tokens == NULL) {
                free_tokens(tokens, count);
                regfree(&regex);
                return NULL;
            }
            tokens = new_tokens;
            capacity = new_capacity;
        }

        token = copy_token(cursor, token_length);
        if (token == NULL) {
            free_tokens(tokens, count);
            regfree(&regex);
            return NULL;
        }
        tokens[count] = token;
        count++;

        if (last) {
            break;
        }

        cursor += advance;
        if (cursor > end) {
            cursor = end;
        }
    }

    regfree(&regex);
    *token_count = count;
    return tokens;
}

int main(void)
{
    const char input[] = "apple, banana;cherry  grape|melon";
    const char *pattern = "[,;|[:space:]]+";
    char **tokens;
    size_t count = 0;
    size_t i;

    tokens = regex_split(input, sizeof(input) - 1, pattern, &count);
    if (tokens == NULL) {
        fprintf(stderr, "Failed to split the input string.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("Token %zu: '%s'\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}