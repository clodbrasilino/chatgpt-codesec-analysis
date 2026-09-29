#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *str, const char *pattern, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t capacity = 10;
    size_t len;
    char **result = NULL;
    char *temp = NULL;
    const char *cursor = str;
    size_t offset = 0;

    if (str == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
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

        len = match.rm_so;
        if (*count >= capacity) {
            capacity *= 2;
            char **new_result = realloc(result, capacity * sizeof(char *));
            if (new_result == NULL) {
                for (size_t i = 0; i < *count; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
        }

        temp = malloc(len + 1);
        if (temp == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        memcpy(temp, cursor, len);
        temp[len] = '\0';
        result[*count] = temp;
        (*count)++;

        offset = match.rm_eo;
        cursor += offset;
    }

    len = strlen(cursor);
    if (*count >= capacity) {
        capacity += 1;
        char **new_result = realloc(result, capacity * sizeof(char *));
        if (new_result == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = new_result;
    }

    temp = malloc(len + 1);
    if (temp == NULL) {
        for (size_t i = 0; i < *count; i++) {
            free(result[i]);
        }
        free(result);
        regfree(&regex);
        return NULL;
    }

    memcpy(temp, cursor, len);
    temp[len] = '\0';
    result[*count] = temp;
    (*count)++;

    regfree(&regex);

    char **final_result = realloc(result, (*count + 1) * sizeof(char *));
    if (final_result == NULL) {
        for (size_t i = 0; i < *count; i++) {
            free(result[i]);
        }
        free(result);
        return NULL;
    }
    result = final_result;
    result[*count] = NULL;

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
    const char *str = "Hello,world;this|is/a.test";
    const char *pattern = "[,;/|\\.]+";
    size_t count = 0;

    char **tokens = split_string(str, pattern, &count);
    if (tokens == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
    }

    free_split_result(tokens);

    return EXIT_SUCCESS;
}