#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_at_lowercase(const char *str, size_t *count);
void free_split_result(char **tokens);

char **split_at_lowercase(const char *str, size_t *count)
{
    if (count != NULL) {
        *count = 0;
    }
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t token_count = 0;
    {
        const char *q = str;
        int in_token = 0;
        while (*q) {
            if (islower((unsigned char)*q)) {
                if (in_token) {
                    token_count++;
                    in_token = 0;
                }
            } else {
                if (!in_token) {
                    in_token = 1;
                }
            }
            q++;
        }
        if (in_token) {
            token_count++;
        }
    }

    if (token_count == 0) {
        char **tokens = malloc(sizeof(*tokens));
        if (tokens == NULL) return NULL;
        tokens[0] = NULL;
        *count = 0;
        return tokens;
    }

    char **tokens = malloc((token_count + 1) * sizeof(*tokens));
    if (tokens == NULL) return NULL;

    size_t t_idx = 0;
    const char *p = str;
    const char *start = NULL;

    while (*p) {
        if (islower((unsigned char)*p)) {
            if (start != NULL) {
                size_t token_len = (size_t)(p - start);
                char *token = malloc(token_len + 1);
                if (token == NULL) {
                    for (size_t i = 0; i < t_idx; i++) free(tokens[i]);
                    free(tokens);
                    return NULL;
                }
                memcpy(token, start, token_len);
                token[token_len] = '\0';
                tokens[t_idx++] = token;
                start = NULL;
            }
        } else {
            if (start == NULL) {
                start = p;
            }
        }
        p++;
    }

    if (start != NULL) {
        size_t token_len = (size_t)(p - start);
        char *token = malloc(token_len + 1);
        if (token == NULL) {
            for (size_t i = 0; i < t_idx; i++) free(tokens[i]);
            free(tokens);
            return NULL;
        }
        memcpy(token, start, token_len);
        token[token_len] = '\0';
        tokens[t_idx++] = token;
    }

    tokens[t_idx] = NULL;
    *count = t_idx;
    return tokens;
}

void free_split_result(char **tokens)
{
    if (tokens == NULL) {
        return;
    }
    for (size_t i = 0; tokens[i] != NULL; ++i) {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void)
{
    const char *text = "HelloWorld";
    size_t count = 0;
    char **tokens = split_at_lowercase(text, &count);
    if (tokens == NULL) {
        return 1;
    }

    for (size_t i = 0; i < count; ++i) {
        puts(tokens[i]);
    }

    free_split_result(tokens);
    return 0;
}