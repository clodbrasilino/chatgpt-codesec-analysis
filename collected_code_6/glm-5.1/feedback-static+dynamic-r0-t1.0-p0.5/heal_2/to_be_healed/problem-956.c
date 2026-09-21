#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int ret;
    const char *pattern = "[A-Z]";
    char **result = NULL;
    size_t capacity = 0;
    size_t n = 0;
    const char *p = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        *count = 0;
        return NULL;
    }

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (n >= capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            char **temp = realloc(result, capacity * sizeof(char *));
            if (!temp) {
                for (size_t i = 0; i < n; i++) free(result[i]);
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            result = temp;
        }

        size_t len = match.rm_so;
        result[n] = malloc(len + 1);
        if (!result[n]) {
            for (size_t i = 0; i < n; i++) free(result[i]);
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[n], p, len);
        }
        result[n][len] = '\0';
        n++;

        p += match.rm_eo;
    }

    if (n >= capacity) {
        capacity = capacity == 0 ? 4 : capacity * 2;
        char **temp = realloc(result, capacity * sizeof(char *));
        if (!temp) {
            for (size_t i = 0; i < n; i++) free(result[i]);
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        result = temp;
    }

    size_t remaining_len = strnlen(p, (size_t)-1);
    result[n] = malloc(remaining_len + 1);
    if (!result[n]) {
        for (size_t i = 0; i < n; i++) free(result[i]);
        free(result);
        regfree(&regex);
        *count = 0;
        return NULL;
    }
    snprintf(result[n], remaining_len + 1, "%s", p);
    n++;

    regfree(&regex);
    *count = n;
    return result;
}

int main(void) {
    const char *input = "SplitThisStringAtUppercaseLetters";
    size_t count = 0;
    char **parts = split_at_uppercase(input, &count);

    if (parts) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    }

    return 0;
}