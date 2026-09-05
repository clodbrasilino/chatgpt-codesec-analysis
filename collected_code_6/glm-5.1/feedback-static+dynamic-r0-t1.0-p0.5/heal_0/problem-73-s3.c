#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *str, const char *pattern, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t capacity = 10;
    size_t idx = 0;
    char **result = NULL;
    const char *cursor = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        *count = 0;
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        *count = 0;
        return NULL;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        if (idx >= capacity) {
            capacity *= 2;
            char **temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < idx; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            result = temp;
        }

        size_t len = match.rm_so;
        result[idx] = malloc(len + 1);
        if (result[idx] == NULL) {
            for (size_t i = 0; i < idx; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        memcpy(result[idx], cursor, len);
        result[idx][len] = '\0';
        idx++;

        cursor += match.rm_eo;
    }

    if (idx >= capacity) {
        capacity += 1;
        char **temp = realloc(result, capacity * sizeof(char *));
        if (temp == NULL) {
            for (size_t i = 0; i < idx; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            *count = 0;
            return NULL;
        }
        result = temp;
    }

    size_t remaining_len = strlen(cursor);
    result[idx] = malloc(remaining_len + 1);
    if (result[idx] == NULL) {
        for (size_t i = 0; i < idx; i++) {
            free(result[i]);
        }
        free(result);
        regfree(&regex);
        *count = 0;
        return NULL;
    }

    memcpy(result[idx], cursor, remaining_len);
    result[idx][remaining_len] = '\0';
    idx++;

    regfree(&regex);

    char **final_result = realloc(result, (idx + 1) * sizeof(char *));
    if (final_result != NULL) {
        final_result[idx] = NULL;
        *count = idx;
        return final_result;
    }

    result[idx] = NULL;
    *count = idx;
    return result;
}

void free_split_result(char **result) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *str = "Hello,world;this.is:a/test";
    const char *pattern = "[,;:. /]+";
    size_t count = 0;

    char **tokens = split_string(str, pattern, &count);

    if (tokens != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", tokens[i]);
        }
        free_split_result(tokens);
    }

    return 0;
}