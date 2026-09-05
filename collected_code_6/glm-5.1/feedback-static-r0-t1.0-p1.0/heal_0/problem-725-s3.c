#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **extract_quoted(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t matches[1];
    int ret;
    char **results = NULL;
    size_t capacity = 0;
    *count = 0;

    ret = regcomp(&regex, "\"([^\"]+)\"", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    const char *p = str;
    while (1) {
        ret = regexec(&regex, p, 1, matches, 0);
        if (ret == REG_NOMATCH) {
            break;
        }

        if (matches[0].rm_so == -1) {
            break;
        }

        if (*count >= capacity) {
            capacity = capacity == 0 ? 4 : capacity * 2;
            char **new_results = realloc(results, capacity * sizeof(char *));
            if (!new_results) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            results = new_results;
        }

        size_t start = matches[0].rm_so + 1;
        size_t end = matches[0].rm_eo - 1;
        size_t len = end - start;

        char *val = malloc(len + 1);
        if (!val) {
            for (size_t i = 0; i < *count; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        memcpy(val, p + start, len);
        val[len] = '\0';

        results[*count] = val;
        (*count)++;

        p += matches[0].rm_eo;
    }

    regfree(&regex);
    return results;
}

int main() {
    const char *text = "Extract \"this value\" and \"that value\" from the string.";
    size_t count;
    char **values = extract_quoted(text, &count);

    if (values) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }

    return 0;
}