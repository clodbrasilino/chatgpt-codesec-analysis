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

    size_t len = strlen(str);
    char **tokens = malloc((len + 1) * sizeof(*tokens));
    if (tokens == NULL) {
        return NULL;
    }

    size_t token_count = 0;
    const char *start = NULL;

    for (size_t i = 0; i < len; ++i) {
        if (islower((unsigned char)str[i])) {
            if (start != NULL) {
                size_t token_len = (size_t)(str + i - start);
                char *token = malloc(token_len + 1);
                if (token == NULL) {
                    for (size_t j = 0; j < token_count; ++j) {
                        free(tokens[j]);
                    }
                    free(tokens);
                    return NULL;
                }
                memcpy(token, start, token_len);
                token[token_len] = '\0';
                tokens[token_count++] = token;
                start = NULL;
            }
        } else {
            if (start == NULL) {
                start = str + i;
            }
        }
    }

    if (start != NULL) {
        size_t token_len = (size_t)(str + len - start);
        char *token = malloc(token_len + 1);
        if (token == NULL) {
            for (size_t j = 0; j < token_count; ++j) {
                free(tokens[j]);
            }
            free(tokens);
            return NULL;
        }
        memcpy(token, start, token_len);
        token[token_len] = '\0';
        tokens[token_count++] = token;
    }

    tokens[token_count] = NULL;
    *count = token_count;
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