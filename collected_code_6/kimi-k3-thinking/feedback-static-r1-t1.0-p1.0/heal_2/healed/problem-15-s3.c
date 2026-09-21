#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 65536

static size_t safe_strnlen(const char *s, size_t maxlen)
{
    size_t n = 0;

    while (n < maxlen && s[n] != '\0') {
        n++;
    }

    return n;
}

static void free_token_array(char **tokens, size_t count)
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

char **split_at_lowercase(const char *str, size_t *count)
{
    char **result;
    size_t capacity = 8;
    size_t n = 0;
    size_t len;
    size_t i = 0;

    if (str == NULL || count == NULL) {
        return NULL;
    }

    len = safe_strnlen(str, MAX_INPUT_LEN);

    result = malloc(capacity * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    while (i < len) {
        size_t start;
        size_t tok_len;
        size_t j;
        char *token;

        while (i < len && islower((unsigned char)str[i])) {
            i++;
        }
        start = i;
        while (i < len && !islower((unsigned char)str[i])) {
            i++;
        }
        tok_len = i - start;

        if (tok_len == 0) {
            continue;
        }

        if (n == capacity) {
            char **temp;

            if (capacity > SIZE_MAX / 2 ||
                capacity * 2 > SIZE_MAX / sizeof(*result)) {
                free_token_array(result, n);
                return NULL;
            }
            capacity *= 2;
            temp = realloc(result, capacity * sizeof(*result));
            if (temp == NULL) {
                free_token_array(result, n);
                return NULL;
            }
            result = temp;
        }

        if (tok_len == SIZE_MAX || tok_len > len - start) {
            free_token_array(result, n);
            return NULL;
        }

        token = malloc(tok_len + 1);
        if (token == NULL) {
            free_token_array(result, n);
            return NULL;
        }

        for (j = 0; j < tok_len && start + j < len; j++) {
            token[j] = str[start + j];
        }
        token[j] = '\0';

        if (j != tok_len) {
            free(token);
            free_token_array(result, n);
            return NULL;
        }

        result[n] = token;
        n++;
    }

    if (n + 1 <= SIZE_MAX / sizeof(*result)) {
        char **temp = realloc(result, (n + 1) * sizeof(*result));

        if (temp != NULL) {
            result = temp;
        }
    }

    result[n] = NULL;
    *count = n;
    return result;
}

void free_split(char **tokens, size_t count)
{
    free_token_array(tokens, count);
}

int main(void)
{
    const char *input = "ABCdefGHiJKLmnoPQRstuvWXyz";
    char **tokens;
    size_t count = 0;
    size_t i;

    tokens = split_at_lowercase(input, &count);
    if (tokens == NULL) {
        fprintf(stderr, "Error: failed to split string\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", input);
    printf("Tokens (%zu):\n", count);
    for (i = 0; i < count; i++) {
        printf("[%zu] \"%s\"\n", i, tokens[i]);
    }

    free_split(tokens, count);
    return EXIT_SUCCESS;
}