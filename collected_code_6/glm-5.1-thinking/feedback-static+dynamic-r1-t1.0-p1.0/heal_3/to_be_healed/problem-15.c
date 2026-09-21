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
            for (size_t i = 0; i < size; i++) {
                free(tokens[i]);
            }
            free(tokens);
            return NULL;
        }

        char *token = malloc(len + 1);
        if (token == NULL) {
            for (size_t i = 0; i < size; i++) {
                free(tokens[i]);
            }
            free(tokens);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(token, start, len);
        token[len] = '\0';

        if (size == capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(token);
                for (size_t i = 0; i < size; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                return NULL;
            }
            size_t new_capacity = capacity * 2;
            if (new_capacity > SIZE_MAX / sizeof(char *)) {
                free(token);
                for (size_t i = 0; i < size; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                return NULL;
            }
            char **new_tokens = realloc(tokens, new_capacity * sizeof(char *));
            if (new_tokens == NULL) {
                free(token);
                for (size_t i = 0; i < size; i++) {
                    free(tokens[i]);
                }
                free(tokens);
                return NULL;
            }
            tokens = new_tokens;
            capacity = new_capacity;
        }

        tokens[size++] = token;
    }

    /* Possible weaknesses found:
     *  Assignment 'final_alloc_count=size+1', assigned value is greater than 0
     */
    size_t final_alloc_count = size + 1;
    /* Possible weaknesses found:
     *  Condition 'final_alloc_count==0' is always false [knownConditionTrueFalse]
     *  Condition 'final_alloc_count==0' is always false
     */
    if (final_alloc_count == 0 || final_alloc_count > SIZE_MAX / sizeof(char *)) {
        for (size_t i = 0; i < size; i++) {
            free(tokens[i]);
        }
        free(tokens);
        return NULL;
    }
    char **final_tokens = realloc(tokens, final_alloc_count * sizeof(char *));
    if (final_tokens == NULL) {
        for (size_t i = 0; i < size; i++) {
            free(tokens[i]);
        }
        free(tokens);
        return NULL;
    }
    final_tokens[size] = NULL;

    return final_tokens;
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