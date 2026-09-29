#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *my_strndup(const char *s, size_t n) {
    size_t len = 0;
    while (len < n && s[len]) {
        len++;
    }
    char *new_str = malloc(len + 1);
    if (new_str) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str, s, len);
        new_str[len] = '\0';
    }
    return new_str;
}

char *my_strdup(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);
    char *new_str = malloc(len + 1);
    if (new_str) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str, s, len + 1);
    }
    return new_str;
}

char **split_string_regex(const char *str, const char *pattern, size_t *count) {
    regex_t regex;
    size_t capacity = 10;
    size_t len = 0;

    if (capacity > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }
    char **result = malloc(capacity * sizeof(char *));
    if (!result) {
        return NULL;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        free(result);
        return NULL;
    }

    const char *p = str;
    regmatch_t match;

    while (1) {
        int reti = regexec(&regex, p, 1, &match, 0);
        if (reti == REG_NOMATCH) {
            if (*p) {
                if (len >= capacity) {
                    size_t new_cap = capacity * 2;
                    if (new_cap <= capacity || new_cap > SIZE_MAX / sizeof(char *)) goto cleanup;
                    capacity = new_cap;
                    char **tmp = realloc(result, capacity * sizeof(char *));
                    if (!tmp) goto cleanup;
                    result = tmp;
                }
                result[len] = my_strdup(p);
                if (!result[len]) goto cleanup;
                len++;
            }
            break;
        }

        if (match.rm_so > 0) {
            if (len >= capacity) {
                size_t new_cap = capacity * 2;
                if (new_cap <= capacity || new_cap > SIZE_MAX / sizeof(char *)) goto cleanup;
                capacity = new_cap;
                char **tmp = realloc(result, capacity * sizeof(char *));
                if (!tmp) goto cleanup;
                result = tmp;
            }
            result[len] = my_strndup(p, match.rm_so);
            if (!result[len]) goto cleanup;
            len++;
        }

        p += match.rm_eo;
        if (match.rm_so == match.rm_eo) {
            if (*p) {
                p++;
            } else {
                break;
            }
        }
    }

    regfree(&regex);

    if (len >= capacity) {
        if (len == SIZE_MAX || (len + 1) > SIZE_MAX / sizeof(char *)) {
            for (size_t i = 0; i < len; i++) free(result[i]);
            free(result);
            return NULL;
        }
        size_t new_cap = len + 1;
        capacity = new_cap;
        char **tmp = realloc(result, capacity * sizeof(char *));
        if (!tmp) {
            for (size_t i = 0; i < len; i++) free(result[i]);
            free(result);
            return NULL;
        }
        result = tmp;
    }
    result[len] = NULL;

    if (count) {
        *count = len;
    }

    return result;

cleanup:
    regfree(&regex);
    for (size_t i = 0; i < len; i++) {
        free(result[i]);
    }
    free(result);
    return NULL;
}

int main(void) {
    const char *text = "apple;banana,cherry:date";
    const char *delimiters = "[,;:]";
    size_t count = 0;
    char **tokens = split_string_regex(text, delimiters, &count);

    if (tokens) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    }

    return 0;
}