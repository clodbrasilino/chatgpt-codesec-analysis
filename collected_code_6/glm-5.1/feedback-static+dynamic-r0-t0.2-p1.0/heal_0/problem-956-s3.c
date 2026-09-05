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
    size_t len;

    *count = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        return NULL;
    }

    while (*cursor) {
        status = regexec(&regex, cursor, 1, &match, 0);
        if (status == 0) {
            len = match.rm_so;
            if (len > 0) {
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
                result[idx] = malloc(len + 1);
                if (!result[idx]) {
                    for (size_t i = 0; i < idx; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(result[idx], cursor, len);
                result[idx][len] = '\0';
                idx++;
            }
            cursor += match.rm_so;
        } else {
            len = strlen(cursor);
            if (len > 0) {
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
                result[idx] = malloc(len + 1);
                if (!result[idx]) {
                    for (size_t i = 0; i < idx; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                memcpy(result[idx], cursor, len);
                result[idx][len] = '\0';
                idx++;
            }
            break;
        }
    }

    regfree(&regex);

    char **final_result = realloc(result, (idx + 1) * sizeof(char *));
    if (!final_result) {
        for (size_t i = 0; i < idx; i++) free(result[i]);
        free(result);
        return NULL;
    }
    result = final_result;
    result[idx] = NULL;
    *count = idx;

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