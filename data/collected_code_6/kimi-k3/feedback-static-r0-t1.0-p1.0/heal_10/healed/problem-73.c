#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char **split_string(const char *str, size_t str_len, const char *pattern, int *count) {
    regex_t regex;
    regmatch_t match;
    char **result = NULL;
    int capacity = 10;
    int size = 0;
    const char *current = str;
    size_t remaining = str_len;
    int ret;

    if (str == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc((size_t)capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (remaining > 0) {
        ret = regexec(&regex, current, 1, &match, 0);
        
        if (ret == REG_NOMATCH) {
            break;
        }

        if (match.rm_so > 0) {
            if (size >= capacity) {
                char **temp;
                capacity *= 2;
                temp = realloc(result, (size_t)capacity * sizeof(char *));
                if (temp == NULL) {
                    goto cleanup;
                }
                result = temp;
            }

            size_t len = (size_t)match.rm_so;
            if (len > remaining || len == SIZE_MAX) {
                goto cleanup;
            }
            result[size] = malloc(len + 1);
            if (result[size] == NULL) {
                goto cleanup;
            }
            if (len > 0) {
                memcpy(result[size], current, len);
            }
            result[size][len] = '\0';
            size++;
        }

        if ((size_t)match.rm_eo > remaining) {
            goto cleanup;
        }
        current += match.rm_eo;
        remaining -= (size_t)match.rm_eo;
    }

    if (remaining > 0) {
        if (size >= capacity) {
            char **temp;
            capacity += 1;
            temp = realloc(result, (size_t)capacity * sizeof(char *));
            if (temp == NULL) {
                goto cleanup;
            }
            result = temp;
        }

        size_t len = remaining;
        if (len == SIZE_MAX) {
            goto cleanup;
        }
        result[size] = malloc(len + 1);
        if (result[size] == NULL) {
            goto cleanup;
        }
        memcpy(result[size], current, len);
        result[size][len] = '\0';
        size++;
    }

    regfree(&regex);
    *count = size;
    return result;

cleanup:
    for (int i = 0; i < size; i++) {
        free(result[i]);
    }
    free(result);
    regfree(&regex);
    return NULL;
}

void free_split_result(char **result, int count) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char input[] = "apple,banana;cherry:grape|orange";
    const char *pattern = "[,;:|]";
    int count = 0;
    char **tokens;
    size_t input_len = sizeof(input) - 1;

    tokens = split_string(input, input_len, pattern, &count);
    
    if (tokens == NULL) {
        fprintf(stderr, "Error splitting string\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
    }

    free_split_result(tokens, count);
    return EXIT_SUCCESS;
}