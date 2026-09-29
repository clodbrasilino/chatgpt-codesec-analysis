#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char **split_at_lowercase(const char *str, int *count)
{
    size_t lower_count = 0;
    const char *p;
    size_t token_count;
    char **tokens;
    size_t idx = 0;
    const char *start;

    if (str == NULL || count == NULL) {
        return NULL;
    }

    for (p = str; *p != '\0'; p++) {
        if (*p >= 'a' && *p <= 'z') {
            lower_count++;
        }
    }

    token_count = lower_count + 1;

    if (token_count > (size_t)INT_MAX) {
        *count = 0;
        return NULL;
    }

    tokens = malloc((token_count + 1) * sizeof(char *));
    if (tokens == NULL) {
        *count = 0;
        return NULL;
    }

    start = str;

    while (1) {
        const char *delim = start;
        size_t len;

        while (*delim != '\0' && !(*delim >= 'a' && *delim <= 'z')) {
            delim++;
        }

        len = (size_t)(delim - start);

        tokens[idx] = malloc(len + 1);
        if (tokens[idx] == NULL) {
            size_t i;
            for (i = 0; i < idx; i++) {
                free(tokens[i]);
            }
            free(tokens);
            *count = 0;
            return NULL;
        }

        if (len > 0) {
            memcpy(tokens[idx], start, len);
        }
        tokens[idx][len] = '\0';
        idx++;

        if (*delim == '\0') {
            break;
        }

        start = delim + 1;
    }

    tokens[token_count] = NULL;
    *count = (int)token_count;

    return tokens;
}

int main(void)
{
    int count;
    char **tokens = split_at_lowercase("HelloWorld", &count);
    int i;

    if (tokens == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (i = 0; i < count; i++) {
        printf("[%s]\n", tokens[i]);
        free(tokens[i]);
    }

    free(tokens);

    return 0;
}