#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    int capacity = 10;
    char **result = malloc((size_t)capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    int start = 0;
    int num_tokens = 0;
    int i = 0;

    while (1) {
        if (str[i] == '\0' || islower((unsigned char)str[i])) {
            size_t token_len = (size_t)(i - start);

            if (token_len > 0) {
                if (num_tokens >= capacity) {
                    int new_capacity_val = capacity * 2;
                    if (new_capacity_val < capacity) {
                        for (int j = 0; j < num_tokens; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    size_t new_capacity = (size_t)capacity * 2;
                    if (new_capacity > SIZE_MAX / sizeof(char *)) {
                        for (int j = 0; j < num_tokens; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char **temp = realloc(result, new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < num_tokens; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    capacity = (int)new_capacity;
                }

                if (token_len >= SIZE_MAX) {
                    for (int j = 0; j < num_tokens; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                result[num_tokens] = malloc(token_len + 1);
                if (result[num_tokens] == NULL) {
                    for (int j = 0; j < num_tokens; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                if (str + start == NULL || token_len > strlen(str + start)) {
                    free(result[num_tokens]);
                    for (int j = 0; j < num_tokens; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                memcpy(result[num_tokens], str + start, token_len);
                result[num_tokens][token_len] = '\0';
                num_tokens++;
            }
            if (str[i] == '\0') {
                break;
            }
            start = i + 1;
        }
        i++;
    }

    *count = num_tokens;
    return result;
}

int main(void) {
    const char *test_str = "HelloWorldThisIsATest";
    int count = 0;
    char **tokens = split_at_lowercase(test_str, &count);

    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
        free(tokens[i]);
    }
    free(tokens);

    return 0;
}