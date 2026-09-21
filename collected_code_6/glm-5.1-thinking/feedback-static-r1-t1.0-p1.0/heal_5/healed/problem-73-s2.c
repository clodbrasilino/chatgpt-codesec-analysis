#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char **split_string_regex(const char *str, size_t str_len, const char *pattern, size_t *out_count) {
    if (str == NULL || pattern == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret;
    size_t capacity = 8;
    size_t count = 0;
    char **result = NULL;
    const char *p = str;
    regmatch_t match;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    if (capacity > SIZE_MAX / sizeof(char *)) {
        regfree(&regex);
        return NULL;
    }
    size_t alloc_size = capacity * sizeof(char *);
    result = malloc(alloc_size);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (1) {
        ret = regexec(&regex, p, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            size_t len = str_len - (p - str);
            if (len > 0) {
                if (len == SIZE_MAX) {
                    goto cleanup;
                }
                if (count >= capacity) {
                    if (capacity > SIZE_MAX / 2) goto cleanup;
                    size_t new_capacity = capacity * 2;
                    if (new_capacity > SIZE_MAX / sizeof(char *)) goto cleanup;
                    alloc_size = new_capacity * sizeof(char *);
                    char **temp = realloc(result, alloc_size);
                    if (temp == NULL) goto cleanup;
                    result = temp;
                    capacity = new_capacity;
                }
                result[count] = malloc(len + 1);
                if (result[count] == NULL) goto cleanup;
                memcpy(result[count], p, len);
                result[count][len] = '\0';
                count++;
            }
            break;
        }

        if (match.rm_so > 0) {
            size_t so_len = (size_t)match.rm_so;
            if (so_len == SIZE_MAX) goto cleanup;
            if (count >= capacity) {
                if (capacity > SIZE_MAX / 2) goto cleanup;
                size_t new_capacity = capacity * 2;
                if (new_capacity > SIZE_MAX / sizeof(char *)) goto cleanup;
                alloc_size = new_capacity * sizeof(char *);
                char **temp = realloc(result, alloc_size);
                if (temp == NULL) goto cleanup;
                result = temp;
                capacity = new_capacity;
            }
            result[count] = malloc(so_len + 1);
            if (result[count] == NULL) goto cleanup;
            memcpy(result[count], p, so_len);
            result[count][so_len] = '\0';
            count++;
        }

        p += match.rm_eo;
        if (match.rm_so == match.rm_eo) {
            if (*p == '\0') {
                break;
            }
            p++;
        }
    }

    if (count >= capacity) {
        if (capacity == SIZE_MAX) goto cleanup;
        size_t new_capacity = capacity + 1;
        if (new_capacity > SIZE_MAX / sizeof(char *)) goto cleanup;
        alloc_size = new_capacity * sizeof(char *);
        char **temp = realloc(result, alloc_size);
        if (temp == NULL) goto cleanup;
        result = temp;
    }
    result[count] = NULL;
    if (out_count != NULL) {
        *out_count = count;
    }
    regfree(&regex);
    return result;

cleanup:
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
    regfree(&regex);
    return NULL;
}

int main(void) {
    const char *str = "Hello, world! This;is a test.";
    const char *pattern = "[, !;]+";
    size_t count = 0;
    size_t str_len = sizeof("Hello, world! This;is a test.") - 1;
    char **tokens = split_string_regex(str, str_len, pattern, &count);

    if (tokens != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Token %zu: %s\n", i, tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    }

    return 0;
}