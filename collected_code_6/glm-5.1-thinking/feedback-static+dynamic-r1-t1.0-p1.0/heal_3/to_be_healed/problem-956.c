#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int add_string(char ***result, size_t *count, size_t *capacity, const char *start, size_t len) {
    if (*count >= *capacity) {
        *capacity *= 2;
        char **new_result = realloc(*result, *capacity * sizeof(char *));
        if (new_result == NULL) {
            return -1;
        }
        *result = new_result;
    }
    
    char *s = malloc(len + 1);
    if (s == NULL) {
        return -1;
    }
    
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(s, start, len);
    s[len] = '\0';
    
    (*result)[(*count)++] = s;
    return 0;
}

char **split_at_uppercase(const char *str, size_t *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t str_len = strlen(str);
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

    const char *ptr = str;
    regmatch_t match;

    while (regexec(&regex, ptr, 1, &match, 0) == 0) {
        if (match.rm_so > 0) {
            if (add_string(&result, count, &capacity, ptr, match.rm_so) != 0) {
                goto cleanup;
            }
        }

        size_t match_len = match.rm_eo - match.rm_so;
        if (add_string(&result, count, &capacity, ptr + match.rm_so, match_len) != 0) {
            goto cleanup;
        }

        ptr += match.rm_eo;
    }

    size_t suffix_len = str_len - (ptr - str);
    if (suffix_len > 0) {
        if (add_string(&result, count, &capacity, ptr, suffix_len) != 0) {
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