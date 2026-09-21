#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

static void free_partial(char **tokens, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

char **split_at_uppercase(const char *input, size_t *count)
{
    regex_t regex;
    regmatch_t match;
    char **result = NULL;
    char **temp = NULL;
    size_t capacity = 8;
    size_t n = 0;
    const char *cursor = NULL;
    size_t remaining;
    int rc;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    remaining = strnlen(input, MAX_INPUT_LEN);
    if (remaining >= MAX_INPUT_LEN) {
        return NULL;
    }

    cursor = input;

    rc = regcomp(&regex, "[A-Z][^A-Z]*|^[^A-Z]+", REG_EXTENDED);
    if (rc != 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (*cursor != '\0') {
        rc = regexec(&regex, cursor, 1, &match, 0);
        if (rc != 0) {
            break;
        }

        if (match.rm_so != 0 || match.rm_eo <= 0) {
            break;
        }

        size_t len = (size_t)match.rm_eo;

        if (len > remaining || len >= MAX_INPUT_LEN) {
            break;
        }

        char *token = malloc(len + 1);
        if (token == NULL) {
            free_partial(result, n);
            regfree(&regex);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, cursor, len);
        token[len] = '\0';

        if (n >= capacity) {
            if (capacity > SIZE_MAX / (2 * sizeof(char *))) {
                free(token);
                free_partial(result, n);
                regfree(&regex);
                return NULL;
            }
            capacity *= 2;
            temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                free(token);
                free_partial(result, n);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        result[n] = token;
        n++;
        cursor += len;
        remaining -= len;
    }

    regfree(&regex);
    *count = n;
    return result;
}

void free_tokens(char **tokens, size_t count)
{
    if (tokens == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void)
{
    const char *text = "helloWorldThisIsATestString";
    size_t count = 0;
    char **tokens = split_at_uppercase(text, &count);

    if (tokens == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", text);
    for (size_t i = 0; i < count; i++) {
        printf("Token %zu: %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}