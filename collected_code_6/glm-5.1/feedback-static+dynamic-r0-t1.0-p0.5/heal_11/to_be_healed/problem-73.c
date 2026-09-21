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
    char **new_result = NULL;
    char *temp = NULL;
    const char *cursor;
    const char *start;

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

    cursor = str;

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH || match.rm_so == -1) {
            break;
        }

        len = match.rm_so;
        if (*count >= capacity) {
            capacity *= 2;
            new_result = realloc(result, capacity * sizeof(char *));
            if (new_result == NULL) {
                for (size_t i = 0; i < *count; i++) free(result[i]);
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
        }

        temp = malloc(len + 1);
        if (temp == NULL) {
            for (size_t i = 0; i < *count; i++) free(result[i]);
            free(result);
            regfree(&regex);
            return NULL;
        }

        start = cursor;
        if (len > 0) {
            if (len <= (size_t)-1 - 1) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(temp, start, len);
            }
        }
        temp[len] = '\0';
        result[*count] = temp;
        (*count)++;

        cursor += match.rm_eo;
        
        if (match.rm_eo == 0) {
            if (*cursor != '\0') {
                cursor++;
            } else {
                break;
            }
        }
    }

    start = cursor;
    while (*start != '\0') {
        start++;
    }
    len = start - cursor;
    
    if (*count >= capacity) {
        capacity += 1;
        new_result = realloc(result, capacity * sizeof(char *));
        if (new_result == NULL) {
            for (size_t i = 0; i < *count; i++) free(result[i]);
            free(result);
            regfree(&regex);
            return NULL;
        }
        result = new_result;
    }

    temp = malloc(len + 1);
    if (temp == NULL) {
        for (size_t i = 0; i < *count; i++) free(result[i]);
        free(result);
        regfree(&regex);
        return NULL;
    }

    start = cursor;
    if (len > 0) {
        if (len <= (size_t)-1 - 1) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp, start, len);
        }
    }
    temp[len] = '\0';
    result[*count] = temp;
    (*count)++;

    regfree(&regex);

    char **final_result = realloc(result, (*count + 1) * sizeof(char *));
    if (final_result == NULL) {
        for (size_t i = 0; i < *count; i++) free(result[i]);
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