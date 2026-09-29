#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_at_lowercase(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t capacity = 8;
    size_t size = 0;
    char **tokens = malloc(capacity * sizeof(char *));
    if (tokens == NULL) {
        return NULL;
    }

    const char *ptr = str;
    while (*ptr != '\0') {
        while (*ptr != '\0' && islower((unsigned char)*ptr)) {
            ptr++;
        }
        if (*ptr == '\0') {
            break;
        }

        const char *start = ptr;
        while (*ptr != '\0' && !islower((unsigned char)*ptr)) {
            ptr++;
        }

        size_t len = (size_t)(ptr - start);
        if (len == SIZE_MAX) {
            goto cleanup;
        }

        /* Possible weaknesses found:
         *  token_size is assigned 'len+1' here.
         */
        size_t token_size = len + 1;
        /* Possible weaknesses found:
         *  Condition 'token_size<=len' is always false [knownConditionTrueFalse]
         *  Condition 'token_size<=len' is always false
         */
        if (token_size <= len) {
            goto cleanup;
        }

        char *token = malloc(token_size);
        if (token == NULL) {
            goto cleanup;
        }

        snprintf(token, token_size, "%.*s", (int)len, start);

        if (size == capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(token);
                goto cleanup;
            }
            size_t new_capacity = capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                free(token);
                goto cleanup;
            }
            char **new_tokens = realloc(tokens, new_capacity * sizeof(char *));
            if (new_tokens == NULL) {
                free(token);
                goto cleanup;
            }
            tokens = new_tokens;
            capacity = new_capacity;
        }

        tokens[size++] = token;
    }

    size_t final_alloc_count = size + 1;
    if (size == SIZE_MAX || final_alloc_count > SIZE_MAX / sizeof(char *)) {
        goto cleanup;
    }
    char **final_tokens = realloc(tokens, final_alloc_count * sizeof(char *));
    if (final_tokens == NULL) {
        goto cleanup;
    }
    final_tokens[size] = NULL;

    return final_tokens;

cleanup:
    for (size_t i = 0; i < size; i++) {
        free(tokens[i]);
    }
    free(tokens);
    return NULL;
}

void free_tokens(char **tokens) {
    if (tokens == NULL) {
        return;
    }
    for (size_t i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

int main(void) {
    const char *input = "HelloWorld123testDataSplit";
    char **tokens = split_at_lowercase(input);
    if (tokens != NULL) {
        for (size_t i = 0; tokens[i] != NULL; i++) {
            printf("%s\n", tokens[i]);
        }
        free_tokens(tokens);
    }
    return 0;
}