#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static int add_string(char ***result, size_t *count, size_t *capacity, const char *start, size_t len) {
    if (*count >= *capacity) {
        size_t new_capacity;
        if (*capacity == 0) {
            new_capacity = 1;
        } else if (*capacity > SIZE_MAX - *capacity) {
            return -1;
        } else {
            new_capacity = *capacity * 2;
        }

        size_t alloc_size = new_capacity * sizeof(char *);
        if (alloc_size / sizeof(char *) != new_capacity) {
            return -1;
        }

        char **new_result = realloc(*result, alloc_size);
        if (new_result == NULL) {
            return -1;
        }
        *result = new_result;
        *capacity = new_capacity;
    }

    /* Possible weaknesses found:
     *  s_size is assigned 'len+1' here.
     */
    size_t s_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 's_size<=len' is always false
     *  Condition 's_size<=len' is always false [knownConditionTrueFalse]
     */
    if (s_size <= len) {
        return -1;
    }

    char *s = malloc(s_size);
    if (s == NULL) {
        return -1;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(s, start, len);
    }
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
    size_t alloc_size = capacity * sizeof(char *);
    if (alloc_size / sizeof(char *) != capacity) {
        regfree(&regex);
        return NULL;
    }
    char **result = malloc(alloc_size);
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

    size_t consumed = ptr - str;
    if (consumed < str_len) {
        size_t suffix_len = str_len - consumed;
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