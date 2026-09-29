#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_MATCHES 100

char **extract_quoted_values(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t matches[MAX_MATCHES];
    char **results = NULL;
    *count = 0;

    if (regcomp(&regex, "\"([^\"]*)\"", REG_EXTENDED) != 0) {
        return NULL;
    }

    const char *p = str;
    size_t capacity = 10;
    results = malloc(capacity * sizeof(char *));
    if (!results) {
        regfree(&regex);
        return NULL;
    }

    while (regexec(&regex, p, MAX_MATCHES, matches, 0) == 0) {
        if (matches[1].rm_so == -1) {
            break;
        }

        if (*count >= capacity) {
            capacity *= 2;
            char **temp = realloc(results, capacity * sizeof(char *));
            if (!temp) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                return NULL;
            }
            results = temp;
        }

        size_t len = matches[1].rm_eo - matches[1].rm_so;
        if (len == 0) {
            results[*count] = malloc(1);
            if (!results[*count]) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                return NULL;
            }
            results[*count][0] = '\0';
        } else if (len < SIZE_MAX) {
            results[*count] = malloc(len + 1);
            if (!results[*count]) {
                for (size_t i = 0; i < *count; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                return NULL;
            }
            memcpy(results[*count], p + matches[1].rm_so, len);
            results[*count][len] = '\0';
        } else {
            break;
        }

        (*count)++;
        p += matches[0].rm_eo;
    }

    regfree(&regex);

    if (*count == 0) {
        free(results);
        return NULL;
    }

    char **shrunk = realloc(results, *count * sizeof(char *));
    if (shrunk) {
        return shrunk;
    }
    return results;
}

int main(void) {
    const char *text = "Hello \"World\", this is a \"test\" string with \"empty\" \"\" quotes.";
    size_t count = 0;
    char **values = extract_quoted_values(text, &count);

    if (values) {
        for (size_t i = 0; i < count; i++) {
            printf("%s\n", values[i]);
            free(values[i]);
        }
        free(values);
    }

    return 0;
}