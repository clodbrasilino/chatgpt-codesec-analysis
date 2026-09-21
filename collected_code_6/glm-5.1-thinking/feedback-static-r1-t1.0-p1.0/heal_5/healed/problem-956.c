#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static int add_token(char ***result, size_t *count, size_t *capacity, const char *start, size_t len) {
    if (len == SIZE_MAX) {
        return -1;
    }
    
    size_t token_size = len + 1;
    
    char *token = malloc(token_size);
    if (token == NULL) {
        return -1;
    }
    
    memcpy(token, start, len);
    token[len] = '\0';

    if (*count >= *capacity) {
        size_t base = (*capacity > 0) ? *capacity : 1;
        if (base > SIZE_MAX / 2) {
            free(token);
            return -1;
        }
        size_t new_cap = base * 2;
        if (new_cap > SIZE_MAX / sizeof(char *)) {
            free(token);
            return -1;
        }
        char **new_result = realloc(*result, new_cap * sizeof(char *));
        if (new_result == NULL) {
            free(token);
            return -1;
        }
        *result = new_result;
        *capacity = new_cap;
    }
    
    (*result)[(*count)++] = token;
    return 0;
}

char **split_at_uppercase(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    regex_t regex;
    if (regcomp(&regex, "([A-Z][^A-Z]*)", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t capacity = 8;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t str_len = strlen(str);
    const char *ptr = str;
    regmatch_t match;

    while (regexec(&regex, ptr, 1, &match, 0) == 0) {
        if (match.rm_so > 0) {
            if (add_token(&result, count, &capacity, ptr, match.rm_so) != 0) {
                goto cleanup;
            }
        }

        size_t match_len = match.rm_eo - match.rm_so;
        if (match_len == 0) {
            if (*ptr == '\0') {
                break;
            }
            ptr++;
            continue;
        }
        
        if (add_token(&result, count, &capacity, ptr + match.rm_so, match_len) != 0) {
            goto cleanup;
        }

        ptr += match.rm_eo;
    }

    if (*ptr != '\0') {
        size_t remaining = str_len - (ptr - str);
        size_t suffix_len = strnlen(ptr, remaining);
        if (add_token(&result, count, &capacity, ptr, suffix_len) != 0) {
            goto cleanup;
        }
    }

    regfree(&regex);
    return result;

cleanup:
    for (size_t i = 0; i < *count; i++) {
        free(result[i]);
    }
    free(result);
    regfree(&regex);
    return NULL;
}

void free_split_result(char **result, size_t count) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *input = "SplitThisStringAtUppercase";
    size_t count = 0;
    char **result = split_at_uppercase(input, &count);

    if (result != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free_split_result(result, count);
    }

    return 0;
}