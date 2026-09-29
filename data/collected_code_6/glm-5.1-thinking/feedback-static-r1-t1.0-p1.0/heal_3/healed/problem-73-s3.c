#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

char *my_strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    if (len == SIZE_MAX) return NULL;
    char *new_str = malloc(len + 1);
    if (new_str) {
        memmove(new_str, s, len);
        new_str[len] = '\0';
    }
    return new_str;
}

char *my_strdup(const char *s) {
    size_t max_len = SIZE_MAX - 1;
    size_t len = strnlen(s, max_len);
    if (len == max_len) return NULL;
    char *new_str = malloc(len + 1);
    if (new_str) {
        memmove(new_str, s, len + 1);
    }
    return new_str;
}

char **split_string_regex(const char *str, const char *pattern, size_t *count) {
    regex_t regex;
    size_t capacity = 10;
    size_t len = 0;
    char **result = NULL;

    if (capacity > SIZE_MAX / sizeof(char *)) return NULL;
    result = malloc(capacity * sizeof(char *));
    if (!result) return NULL;

    if (regcomp(&regex, pattern, REG_EXTENDED)) {
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
                    if (capacity > SIZE_MAX / 2) goto fail;
                    capacity *= 2;
                    if (capacity > SIZE_MAX / sizeof(char *)) goto fail;
                    char **tmp = realloc(result, capacity * sizeof(char *));
                    if (!tmp) goto fail;
                    result = tmp;
                }
                result[len] = my_strdup(p);
                if (!result[len]) goto fail;
                len++;
            }
            break;
        }

        if (match.rm_so > 0) {
            if (len >= capacity) {
                if (capacity > SIZE_MAX / 2) goto fail;
                capacity *= 2;
                if (capacity > SIZE_MAX / sizeof(char *)) goto fail;
                char **tmp = realloc(result, capacity * sizeof(char *));
                if (!tmp) goto fail;
                result = tmp;
            }
            result[len] = my_strndup(p, match.rm_so);
            if (!result[len]) goto fail;
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
        if (len == SIZE_MAX) goto fail_after_regex;
        capacity = len + 1;
        if (capacity > SIZE_MAX / sizeof(char *)) goto fail_after_regex;
        char **tmp = realloc(result, capacity * sizeof(char *));
        if (!tmp) goto fail_after_regex;
        result = tmp;
    }
    result[len] = NULL;

    if (count) *count = len;
    return result;

fail:
    regfree(&regex);
fail_after_regex:
    for (size_t i = 0; i < len; i++) free(result[i]);
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