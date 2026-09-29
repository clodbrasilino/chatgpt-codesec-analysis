#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char** split_at_uppercase(const char* str, size_t* count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[A-Z][^A-Z]*", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t capacity = 10;
    *count = 0;
    char** result = malloc(capacity * sizeof(char*));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char* p = str;
    regmatch_t match;

    while (1) {
        ret = regexec(&regex, p, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }

        if (ret != 0) {
            for (size_t i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (*count >= capacity) {
            capacity *= 2;
            char** new_result = realloc(result, capacity * sizeof(char*));
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

        size_t len = match.rm_eo - match.rm_so;
        char* token = malloc(len + 1);
        if (token == NULL) {
            for (size_t i = 0; i < *count; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        snprintf(token, len + 1, "%.*s", (int)len, p + match.rm_so);

        result[*count] = token;
        (*count)++;

        p += match.rm_eo;
    }

    regfree(&regex);

    char** final_result = realloc(result, (*count + 1) * sizeof(char*));
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

void free_split_result(char** result) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char* input = "HelloWorldThisIsATest";
    size_t count = 0;
    char** result = split_at_uppercase(input, &count);

    if (result != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", result[i]);
        }
        free_split_result(result);
    }

    return 0;
}