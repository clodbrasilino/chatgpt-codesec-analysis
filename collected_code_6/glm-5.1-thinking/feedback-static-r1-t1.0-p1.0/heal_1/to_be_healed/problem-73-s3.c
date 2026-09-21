#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *my_strndup(const char *s, size_t n) {
    char *new_str = malloc(n + 1);
    if (new_str) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str, s, n);
        new_str[n] = '\0';
    }
    return new_str;
}

char *my_strdup(const char *s) {
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s) + 1;
    char *new_str = malloc(len);
    if (new_str) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(new_str, s, len);
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