#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **split_at_lowercase(const char *str, size_t *out_count) {
    if (!str || !out_count) {
        return NULL;
    }

    size_t capacity = 8;
    size_t count = 0;
    char **result = malloc(capacity * sizeof(char *));
    
    if (!result) {
        return NULL;
    }

    const char *start = str;
    const char *p = str;
    int done = 0;

    while (!done) {
        if (*p == '\0' || islower((unsigned char)*p)) {
            if (*p == '\0') {
                done = 1;
            }

            if (count >= capacity) {
                size_t new_cap = capacity * 2;
                char **new_result = realloc(result, new_cap * sizeof(char *));
                if (!new_result) {
                    for (size_t i = 0; i < count; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                result = new_result;
                capacity = new_cap;
            }

            size_t len = (size_t)(p - start);
            char *token = malloc(len + 1);
            if (!token) {
                for (size_t i = 0; i < count; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }

            for (size_t i = 0; i < len; i++) {
                token[i] = start[i];
            }
            token[len] = '\0';
            
            result[count++] = token;

            start = p + 1;
        }
        if (!done) {
            p++;
        }
    }

    *out_count = count;
    return result;
}

void free_split_result(char **result, size_t count) {
    if (!result) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *input_string = "HELLOaWORLDbTESTc";
    size_t count = 0;
    
    char **tokens = split_at_lowercase(input_string, &count);
    
    if (!tokens) {
        fprintf(stderr, "Memory allocation failed or invalid input.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("Token %zu: '%s'\n", i, tokens[i]);
    }

    free_split_result(tokens, count);

    return EXIT_SUCCESS;
}