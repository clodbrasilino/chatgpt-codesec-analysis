#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int status;
    const char *pattern = "[A-Z]";
    char **result = NULL;
    size_t capacity = 0;
    size_t idx = 0;
    const char *cursor = str;
    size_t length;
    size_t safe_length;

    *count = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    while (*cursor) {
        status = regexec(&regex, cursor, 1, &match, 0);
        if (status == 0) {
            length = match.rm_so;
            if (length > 0) {
                if (idx >= capacity) {
                    capacity = capacity == 0 ? 4 : capacity * 2;
                    char **temp = realloc(result, capacity * sizeof(char *));
                    if (!temp) {
                        for (size_t i = 0; i < idx; i++) free(result[i]);
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                }
                safe_length = strnlen(cursor, length);
                result[idx] = malloc(safe_length + 1);
                if (!result[idx]) {
                    for (size_t i = 0; i < idx; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                if (safe_length > 0) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[idx], cursor, safe_length);
                }
                result[idx][safe_length] = '\0';
                idx++;
            }
            cursor += match.rm_eo;
        } else {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            safe_length = strlen(cursor);
            if (safe_length > 0) {
                if (idx >= capacity) {
                    capacity = capacity == 0 ? 4 : capacity * 2;
                    char **temp = realloc(result, capacity * sizeof(char *));
                    if (!temp) {
                        for (size_t i = 0; i < idx; i++) free(result[i]);
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                }
                result[idx] = malloc(safe_length + 1);
                if (!result[idx]) {
                    for (size_t i = 0; i < idx; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[idx], cursor, safe_length);
                result[idx][safe_length] = '\0';
                idx++;
            }
            break;
        }
    }

    if (idx >= capacity) {
        char **temp = realloc(result, (idx + 1) * sizeof(char *));
        if (!temp) {
            for (size_t i = 0; i < idx; i++) free(result[i]);
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = temp;
    }
    result[idx] = NULL;

    regfree(&regex);
    *count = idx;
    return result;
}

void free_split_result(char **result, size_t count) {
    if (result) {
        for (size_t i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char *input = "SplitThisStringAtUppercaseLetters";
    size_t count = 0;
    char **parts = split_at_uppercase(input, &count);

    if (parts) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
        }
        free_split_result(parts, count);
    }

    return 0;
}