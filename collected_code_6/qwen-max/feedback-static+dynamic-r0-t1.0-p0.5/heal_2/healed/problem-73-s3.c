#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char **split_string(const char *input, const char *delimiters, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    char *str = NULL;
    int nmatch = 1, offset = 0, i = 0;
    char **result = NULL;

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE) != 0) {
        return NULL;
    }

    str = strdup(input);
    if (!str) {
        regfree(&regex);
        return NULL;
    }

    result = malloc(sizeof(char *));
    if (!result) {
        free(str);
        regfree(&regex);
        return NULL;
    }
    *result = NULL;
    *count = 0;

    while (regexec(&regex, str + offset, nmatch, matches, 0) == 0) {
        offset += matches[0].rm_eo;
        if (matches[0].rm_so > 0) {
            char **temp = realloc(result, (i + 2) * sizeof(char *));
            if (!temp) {
                for (int j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                free(str);
                regfree(&regex);
                return NULL;
            }
            result = temp;
            result[i] = strndup(str + offset - matches[0].rm_so, matches[0].rm_so);
            if (!result[i]) {
                for (int j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                free(str);
                regfree(&regex);
                return NULL;
            }
            i++;
            *count = i;
        }
    }

    if (offset < (int)strlen(str)) {
        char **temp = realloc(result, (i + 2) * sizeof(char *));
        if (!temp) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(str);
            regfree(&regex);
            return NULL;
        }
        result = temp;
        result[i] = strdup(str + offset);
        if (!result[i]) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(str);
            regfree(&regex);
            return NULL;
        }
        i++;
        *count = i;
    }

    char **temp = realloc(result, (i + 1) * sizeof(char *));
    if (!temp) {
        for (int j = 0; j < i; j++) {
            free(result[j]);
        }
        free(result);
        free(str);
        regfree(&regex);
        return NULL;
    }
    result = temp;
    result[i] = NULL;

    free(str);
    regfree(&regex);
    return result;
}

int main() {
    const char *input = "apple,orange;banana|grape";
    const char *delimiters = ",;|";
    int count = 0;
    char **result = split_string(input, delimiters, &count);

    if (result) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}