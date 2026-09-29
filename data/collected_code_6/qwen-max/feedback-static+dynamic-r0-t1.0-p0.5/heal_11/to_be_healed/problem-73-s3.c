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

    if (regcomp(&regex, delimiters, REG_EXTENDED | REG_NEWLINE)) {
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
        if (matches[0].rm_so > 0) {
            char **new_result = realloc(result, (i + 2) * sizeof(char *));
            if (!new_result) {
                for (int j = 0; j < i; j++) {
                    free(result[j]);
                }
                free(result);
                free(str);
                regfree(&regex);
                return NULL;
            }
            result = new_result;
            result[i] = strndup(str + offset, matches[0].rm_so - offset);
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
        offset += matches[0].rm_eo;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    if (offset < input_len) {
        char **new_result = realloc(result, (i + 2) * sizeof(char *));
        if (!new_result) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(str);
            regfree(&regex);
            return NULL;
        }
        result = new_result;
        result[i] = strndup(str + offset, input_len - offset);
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

    char **final_result = realloc(result, (i + 1) * sizeof(char *));
    if (!final_result) {
        for (int j = 0; j < i; j++) {
            free(result[j]);
        }
        free(result);
        free(str);
        regfree(&regex);
        return NULL;
    }
    result = final_result;
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