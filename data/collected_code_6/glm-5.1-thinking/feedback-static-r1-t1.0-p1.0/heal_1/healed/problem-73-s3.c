#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *my_strndup(const char *s, size_t n) {
    size_t len = strnlen(s, n);
    char *new_str = malloc(len + 1);
    if (new_str) {
        memcpy(new_str, s, len);
        new_str[len] = '\0';
    }
    return new_str;
}

char *my_strdup(const char *s) {
    size_t len = strlen(s);
    char *new_str = malloc(len + 1);
    if (new_str) {
        memcpy(new_str, s, len + 1);
    }
    return new_str;
}

char **split_string_regex(const char *str, const char *pattern, size_t *count) {
    regex_t regex;
    int reti;
    size_t capacity = 10;
    size_t len = 0;
    char **result = malloc(capacity * sizeof(char *));
    if (!result) {
        return NULL;
    }

    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        free(result);
        return NULL;
    }

    const char *p = str;
    regmatch_t match;

    while (1) {
        reti = regexec(&regex, p, 1, &match, 0);
        if (reti == REG_NOMATCH) {
            if (*p) {
                if (len >= capacity) {
                    capacity *= 2;
                    char **tmp = realloc(result, capacity * sizeof(char *));
                    if (!tmp) {
                        for (size_t i = 0; i < len; i++) free(result[i]);
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = tmp;
                }
                result[len++] = my_strdup(p);
            }
            break;
        }

        if (match.rm_so > 0) {
            if (len >= capacity) {
                capacity *= 2;
                char **tmp = realloc(result, capacity * sizeof(char *));
                if (!tmp) {
                    for (size_t i = 0; i < len; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = tmp;
            }
            result[len++] = my_strndup(p, match.rm_so);
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
        capacity = len + 1;
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