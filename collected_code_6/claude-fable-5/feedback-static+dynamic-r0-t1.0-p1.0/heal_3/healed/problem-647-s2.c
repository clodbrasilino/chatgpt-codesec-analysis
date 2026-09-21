#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

char **split_at_uppercase(const char *input, size_t *count);
void free_tokens(char **tokens, size_t count);

char **split_at_uppercase(const char *input, size_t *count)
{
    size_t len;
    size_t capacity;
    size_t num_tokens;
    size_t start;
    size_t i;
    char **tokens;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == 0 || len >= MAX_INPUT_LEN) {
        return NULL;
    }

    capacity = 8;
    tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        return NULL;
    }

    num_tokens = 0;
    start = 0;

    for (i = 0; i <= len; i++) {
        if (i == len || (isupper((unsigned char)input[i]) && i > start)) {
            size_t token_len = i - start;

            if (token_len > 0) {
                char *token;
                size_t alloc_size;
                size_t j;

                if (num_tokens == capacity) {
                    size_t new_capacity;
                    char **resized;

                    if (capacity > SIZE_MAX / (2 * sizeof(char *))) {
                        free_tokens(tokens, num_tokens);
                        return NULL;
                    }
                    new_capacity = capacity * 2;
                    resized = realloc(tokens, new_capacity * sizeof(char *));
                    if (resized == NULL) {
                        free_tokens(tokens, num_tokens);
                        return NULL;
                    }
                    tokens = resized;
                    capacity = new_capacity;
                }

                if (start > len || token_len > len - start) {
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                if (token_len >= SIZE_MAX) {
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                alloc_size = token_len + 1;
                if (alloc_size <= token_len) {
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                token = malloc(alloc_size);
                if (token == NULL) {
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                for (j = 0; j < token_len && j < alloc_size - 1; j++) {
                    token[j] = input[start + j];
                }
                token[j] = '\0';

                tokens[num_tokens] = token;
                num_tokens++;
            }
            start = i;
        }
    }

    *count = num_tokens;
    return tokens;
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

int main(void)
{
    const char *test = "helloWorldThisIsATest";
    size_t count = 0;
    size_t i;
    char **tokens;

    tokens = split_at_uppercase(test, &count);
    if (tokens == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", test);
    printf("Tokens (%zu):\n", count);
    for (i = 0; i < count; i++) {
        printf("  [%zu] %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}