#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_lowercase_char(unsigned char c)
{
    return c >= 'a' && c <= 'z';
}

char **split_at_lowercase(const char *str, size_t *count)
{
    size_t i;
    size_t start;
    size_t token_index;
    size_t token_count;
    size_t len;
    size_t delimiter_count = 0;
    char **tokens;

    if (str == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }

    len = strlen(str);
    for (i = 0; i < len; i++) {
        if (is_lowercase_char((unsigned char)str[i])) {
            delimiter_count++;
        }
    }

    token_count = delimiter_count + 1;
    tokens = malloc((token_count + 1) * sizeof(*tokens));
    if (tokens == NULL) {
        *count = 0;
        return NULL;
    }

    token_index = 0;
    start = 0;
    for (i = 0; i <= len; i++) {
        if (i == len || is_lowercase_char((unsigned char)str[i])) {
            size_t segment_len = i - start;
            char *token = malloc(segment_len + 1);
            if (token == NULL) {
                size_t j;
                for (j = 0; j < token_index; j++) {
                    free(tokens[j]);
                }
                free(tokens);
                *count = 0;
                return NULL;
            }
            if (segment_len > 0) {
                memcpy(token, str + start, segment_len);
            }
            token[segment_len] = '\0';
            tokens[token_index++] = token;
            start = i + 1;
        }
    }
    tokens[token_index] = NULL;
    *count = token_index;
    return tokens;
}

int main(void)
{
    const char *text = "ABCdEF";
    size_t count = 0;
    size_t i;
    char **parts = split_at_lowercase(text, &count);

    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("[%zu] '%s'\n", i, parts[i]);
    }

    for (i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);

    return EXIT_SUCCESS;
}