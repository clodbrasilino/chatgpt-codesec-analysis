#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096U

char **split_at_lowercase(const char *input, size_t *count);
void free_tokens(char **tokens, size_t count);

char **split_at_lowercase(const char *input, size_t *count)
{
    char **tokens = NULL;
    char **temp = NULL;
    size_t num_tokens = 0;
    size_t start = 0;
    size_t i = 0;
    size_t len = 0;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    for (i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)input[i])) {
            if (i > start) {
                size_t seg_len = i - start;
                size_t alloc_size;
                char *segment;

                if (seg_len >= MAX_INPUT_LEN || seg_len >= SIZE_MAX - 1U) {
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                if (start > len || seg_len > len - start) {
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                alloc_size = seg_len + 1U;

                segment = malloc(alloc_size);
                if (segment == NULL) {
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(segment, &input[start], seg_len);
                segment[seg_len] = '\0';

                if (num_tokens >= (SIZE_MAX / sizeof(char *)) - 1U) {
                    free(segment);
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }

                temp = realloc(tokens, (num_tokens + 1U) * sizeof(char *));
                if (temp == NULL) {
                    free(segment);
                    free_tokens(tokens, num_tokens);
                    return NULL;
                }
                tokens = temp;
                tokens[num_tokens] = segment;
                num_tokens++;
            }
            start = i + 1U;
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
    const char *test = "HELLOworldFOObarBAZ123";
    char **tokens = NULL;
    size_t count = 0;
    size_t i;

    tokens = split_at_lowercase(test, &count);
    if (tokens == NULL) {
        fprintf(stderr, "Failed to split string or no tokens found\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", test);
    printf("Tokens: %zu\n", count);
    for (i = 0; i < count; i++) {
        printf("  [%zu]: %s\n", i, tokens[i]);
    }

    free_tokens(tokens, count);
    return EXIT_SUCCESS;
}