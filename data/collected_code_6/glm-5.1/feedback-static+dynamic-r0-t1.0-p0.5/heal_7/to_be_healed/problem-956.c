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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t total_len = strlen(str);

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
        if (len > 0) {
            result[n] = malloc(len + 1);
            if (!result[n]) {
                for (size_t i = 0; i < n; i++) free(result[i]);
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[n], p, len);
            result[n][len] = '\0';
            n++;
        }

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

    size_t max_remaining = total_len - (p - str);
    size_t remaining_len = strnlen(p, max_remaining);
    
    if (remaining_len > 0) {
        result[n] = malloc(remaining_len + 1);
        if (!result[n]) {
            for (size_t i = 0; i < n; i++) free(result[i]);
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[n], p, remaining_len);
        result[n][remaining_len] = '\0';
        n++;
    }

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