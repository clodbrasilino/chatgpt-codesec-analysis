#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

int split_at_uppercase(const char *input, char ***output, size_t *count) {
    if (input == NULL || output == NULL || count == NULL) {
        return -1;
    }

    *output = NULL;
    *count = 0;

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    size_t capacity = 8;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return -1;
    }

    const char *start = input;
    const char *current = input;
    size_t num_tokens = 0;
    regmatch_t match;

    while (*current != '\0') {
        ret = regexec(&regex, current, 1, &match, 0);
        
        if (ret == 0) {
            size_t len = (size_t)match.rm_so;
            
            if (len > 0) {
                if (len >= SIZE_MAX - 1) {
                    goto cleanup;
                }
                
                char *token = malloc(len + 1);
                if (token == NULL) {
                    goto cleanup;
                }
                
                if (len > 0 && start != NULL) {
                    memcpy(token, start, len);
                    token[len] = '\0';
                } else {
                    free(token);
                    goto cleanup;
                }

                if (num_tokens >= capacity) {
                    if (capacity > SIZE_MAX / 2) {
                        free(token);
                        goto cleanup;
                    }
                    capacity *= 2;
                    char **new_result = realloc(result, capacity * sizeof(char *));
                    if (new_result == NULL) {
                        free(token);
                        goto cleanup;
                    }
                    result = new_result;
                }
                result[num_tokens++] = token;
            }

            current += match.rm_so;
            start = current;
        } else if (ret == REG_NOMATCH) {
            break;
        } else {
            goto cleanup;
        }
    }

    if (*start != '\0' || num_tokens == 0) {
        size_t len = strnlen(start, SIZE_MAX - 1);
        
        if (len >= SIZE_MAX - 1) {
            goto cleanup;
        }
        
        char *token = malloc(len + 1);
        if (token == NULL) {
            goto cleanup;
        }
        
        if (len > 0 && start != NULL) {
            memcpy(token, start, len);
            token[len] = '\0';
        } else if (len == 0) {
            token[0] = '\0';
        } else {
            free(token);
            goto cleanup;
        }

        if (num_tokens >= capacity) {
            if (capacity > SIZE_MAX / 2) {
                free(token);
                goto cleanup;
            }
            capacity *= 2;
            char **new_result = realloc(result, capacity * sizeof(char *));
            if (new_result == NULL) {
                free(token);
                goto cleanup;
            }
            result = new_result;
        }
        result[num_tokens++] = token;
    }

    regfree(&regex);
    *output = result;
    *count = num_tokens;
    return 0;

cleanup:
    for (size_t i = 0; i < num_tokens; i++) {
        free(result[i]);
    }
    free(result);
    regfree(&regex);
    return -1;
}

int main(void) {
    const char *input = "SplitThisStringAtUppercaseLetters";
    char **tokens = NULL;
    size_t count = 0;

    if (split_at_uppercase(input, &tokens, &count) == 0) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    } else {
        fprintf(stderr, "Error splitting string\n");
        return 1;
    }

    return 0;
}