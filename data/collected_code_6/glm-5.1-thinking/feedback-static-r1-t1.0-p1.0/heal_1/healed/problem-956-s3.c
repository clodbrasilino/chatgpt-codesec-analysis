#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *str) {
    regex_t regex;
    int ret;
    char **result = NULL;
    size_t capacity = 0;
    size_t size = 0;

    if (str == NULL) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+[^A-Z]*|[^A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    const char *p = str;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }

        if (match.rm_so == -1) {
            break;
        }

        if (size + 1 >= capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            char **temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < size; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        size_t len = match.rm_eo - match.rm_so;
        char *token = malloc(len + 1);
        if (token == NULL) {
            for (size_t i = 0; i < size; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        snprintf(token, len + 1, "%.*s", (int)len, p + match.rm_so);
        result[size++] = token;

        p += match.rm_eo;
    }

    regfree(&regex);

    if (size + 1 > capacity) {
        char **temp = realloc(result, (size + 1) * sizeof(char *));
        if (temp == NULL) {
            for (size_t i = 0; i < size; i++) {
                free(result[i]);
            }
            free(result);
            return NULL;
        }
        result = temp;
    }

    result[size] = NULL;

    return result;
}

int main(void) {
    const char *input = "HelloWorldThisIsATest";
    char **tokens = split_at_uppercase(input);

    if (tokens != NULL) {
        for (size_t i = 0; tokens[i] != NULL; i++) {
            printf("%s\n", tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    }

    return 0;
}