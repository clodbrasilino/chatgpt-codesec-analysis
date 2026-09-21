#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

static void cleanup(char **result, int count, regex_t *regex) {
    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
    }
    if (regex != NULL) {
        regfree(regex);
    }
}

int find_sequences(const char *input, char ***matches, int *count) {
    regex_t regex;
    regmatch_t pmatch[1];
    const char *pattern = "[A-Z][a-z]+";
    int ret;
    int max_matches = 10;
    int found = 0;
    char **result = NULL;
    const char *p;

    if (input == NULL || matches == NULL || count == NULL) {
        return -1;
    }

    p = input;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        return -1;
    }

    result = (char **)malloc((size_t)max_matches * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return -1;
    }

    while (regexec(&regex, p, 1, pmatch, 0) == 0) {
        if (found >= max_matches) {
            size_t new_size = (size_t)max_matches * 2;
            if (new_size > SIZE_MAX / sizeof(char *)) {
                cleanup(result, found, &regex);
                return -1;
            }
            char **temp = (char **)realloc(result, new_size * sizeof(char *));
            if (temp == NULL) {
                cleanup(result, found, &regex);
                return -1;
            }
            result = temp;
            max_matches = (int)new_size;
        }

        if (pmatch[0].rm_so < 0 || pmatch[0].rm_eo < 0) {
            cleanup(result, found, &regex);
            return -1;
        }

        size_t len = (size_t)(pmatch[0].rm_eo - pmatch[0].rm_so);
        if (len == 0) {
            cleanup(result, found, &regex);
            return -1;
        }

        if (len >= SIZE_MAX) {
            cleanup(result, found, &regex);
            return -1;
        }

        result[found] = (char *)malloc(len + 1);
        if (result[found] == NULL) {
            cleanup(result, found, &regex);
            return -1;
        }

        if (len > 0) {
            if (len + 1 <= len) {
                free(result[found]);
                cleanup(result, found, &regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[found], p + pmatch[0].rm_so, len);
            result[found][len] = '\0';
        } else {
            result[found][0] = '\0';
        }
        found++;

        p += pmatch[0].rm_eo;
    }

    *matches = result;
    *count = found;
    regfree(&regex);
    return 0;
}

int main(void) {
    const char *text = "Hello World This Is A Test String With Uppercase Words Like ABCdef and Xyz";
    char **matches = NULL;
    int count = 0;

    if (find_sequences(text, &matches, &count) == 0) {
        printf("Found %d sequences:\n", count);
        for (int i = 0; i < count; i++) {
            printf("%s\n", matches[i]);
            free(matches[i]);
        }
        free(matches);
    } else {
        printf("Error finding sequences\n");
    }

    return 0;
}