#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 4096

static size_t bounded_strlen(const char *str, size_t max_len)
{
    size_t len = 0;

    while (len < max_len && str[len] != '\0') {
        len++;
    }

    return len;
}

static void free_tokens(char **tokens, size_t n)
{
    size_t j;

    for (j = 0; j < n; j++) {
        free(tokens[j]);
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

    result = malloc(capacity * sizeof(*result));
    if (result == NULL) {
        return NULL;
    }

    len = bounded_strlen(str, MAX_INPUT_LENGTH);

    while (i < len) {
        size_t start;
        size_t tok_len;

        while (i < len && islower((unsigned char)str[i])) {
            i++;
        }
        start = i;
        while (i < len && !islower((unsigned char)str[i])) {
            i++;
        }
        tok_len = i - start;

        if (tok_len > 0) {
            size_t alloc_size;
            char *token;
            int written;

            if (n + 1 >= capacity) {
                char **temp;
                size_t new_capacity;

                if (capacity > SIZE_MAX / 2) {
                    free_tokens(result, n);
                    return NULL;
                }
                new_capacity = capacity * 2;

                if (new_capacity > SIZE_MAX / sizeof(*result)) {
                    free_tokens(result, n);
                    return NULL;
                }

                temp = realloc(result, new_capacity * sizeof(*result));
                if (temp == NULL) {
                    free_tokens(result, n);
                    return NULL;
                }
                result = temp;
                capacity = new_capacity;
            }

            if (tok_len == SIZE_MAX || tok_len > (size_t)INT32_MAX) {
                free_tokens(result, n);
                return NULL;
            }

            if (start > len || tok_len > len - start) {
                free_tokens(result, n);
                return NULL;
            }

            alloc_size = tok_len + 1;

            token = malloc(alloc_size);
            if (token == NULL) {
                free_tokens(result, n);
                return NULL;
            }

            written = snprintf(token, alloc_size, "%.*s", (int)tok_len, str + start);
            if (written < 0 || (size_t)written >= alloc_size) {
                free(token);
                free_tokens(result, n);
                return NULL;
            }

            result[n] = token;
            n++;
        }
    }

    if (n + 1 < capacity) {
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