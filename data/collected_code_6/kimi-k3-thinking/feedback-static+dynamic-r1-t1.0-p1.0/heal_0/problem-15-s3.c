#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    result = malloc(capacity * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    len = strlen(str);

    while (i < len) {
        size_t start;
        size_t tok_len;
        char *token;

        while (i < len && islower((unsigned char)str[i])) {
            i++;
        }
        start = i;
        while (i < len && !islower((unsigned char)str[i])) {
            i++;
        }
        tok_len = i - start;

        if (tok_len > 0) {
            if (n == capacity) {
                char **temp;
                capacity *= 2;
                temp = realloc(result, capacity * sizeof(*result));
                if (temp == NULL) {
                    size_t j;
                    for (j = 0; j < n; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                result = temp;
            }

            token = malloc(tok_len + 1);
            if (token == NULL) {
                size_t j;
                for (j = 0; j < n; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            memcpy(token, str + start, tok_len);
            token[tok_len] = '\0';
            result[n] = token;
            n++;
        }
    }

    {
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
    size_t i;

    if (tokens == NULL) {
        return;
    }

    for (i = 0; i < count; i++) {
        free(tokens[i]);
    }
    free(tokens);
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