#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define MAX_INPUT_LEN 4096

char **split_at_lowercase(const char *input, size_t *count);
void free_tokens(char **tokens, size_t count);

char **split_at_lowercase(const char *input, size_t *count)
{
    char **tokens = NULL;
    char **temp = NULL;
    size_t capacity = 8;
    size_t n = 0;
    size_t start = 0;
    size_t i = 0;
    size_t len;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN && input[MAX_INPUT_LEN - 1] != '\0') {
        return NULL;
    }

    if (capacity > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        return NULL;
    }

    for (i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)input[i])) {
            if (i > start) {
                size_t seg_len = i - start;
                size_t alloc_len;
                char *segment;

                if (seg_len >= SIZE_MAX) {
                    free_tokens(tokens, n);
                    return NULL;
                }

                if (start > len || seg_len > len - start) {
                    free_tokens(tokens, n);
                    return NULL;
                }

                alloc_len = seg_len + 1;
                segment = malloc(alloc_len);
                if (segment == NULL) {
                    free_tokens(tokens, n);
                    return NULL;
                }

                if (seg_len >= alloc_len) {
                    free(segment);
                    free_tokens(tokens, n);
                    return NULL;
                }

                memcpy(segment, input + start, seg_len);
                segment[seg_len] = '\0';

                if (n == capacity) {
                    if (capacity > SIZE_MAX / (2 * sizeof(char *))) {
                        free(segment);
                        free_tokens(tokens, n);
                        return NULL;
                    }
                    capacity *= 2;
                    temp = realloc(tokens, capacity * sizeof(char *));
                    if (temp == NULL) {
                        free(segment);
                        free_tokens(tokens, n);
                        return NULL;
                    }
                    tokens = temp;
                }
                tokens[n] = segment;
                n++;
            }
            start = i + 1;
        }
    }

    *count = n;
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
    const char *text = "HELLOworldFOObarBAZ123";
    char **parts = NULL;
    size_t count = 0;
    size_t i;

    parts = split_at_lowercase(text, &count);
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", text);
    printf("Found %zu segment(s):\n", count);
    for (i = 0; i < count; i++) {
        printf("  [%zu] %s\n", i, parts[i]);
    }

    free_tokens(parts, count);
    return EXIT_SUCCESS;
}