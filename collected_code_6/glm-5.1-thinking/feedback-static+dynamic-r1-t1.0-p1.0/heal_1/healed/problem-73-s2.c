#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string_regex(const char *str, const char *pattern, size_t *out_count) {
    regex_t regex;
    int ret;
    size_t capacity = 8;
    size_t count = 0;
    char **result = NULL;
    const char *p = str;
    regmatch_t match;

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
        ret = regexec(&regex, p, 1, &match, 0);

        if (ret == REG_NOMATCH) {
            if (*p != '\0') {
                if (count >= capacity) {
                    capacity *= 2;
                    char **temp = realloc(result, capacity * sizeof(char *));
                    if (temp == NULL) {
                        goto cleanup;
                    }
                    result = temp;
                }
                result[count] = strdup(p);
                if (result[count] == NULL) {
                    goto cleanup;
                }
                count++;
            }
            break;
        }

        if (match.rm_so > 0) {
            if (count >= capacity) {
                capacity *= 2;
                char **temp = realloc(result, capacity * sizeof(char *));
                if (temp == NULL) {
                    goto cleanup;
                }
                result = temp;
            }
            result[count] = strndup(p, match.rm_so);
            if (result[count] == NULL) {
                goto cleanup;
            }
            count++;
        }

        p += match.rm_eo;
        if (match.rm_so == match.rm_eo) {
            if (*p == '\0') {
                break;
            }
            p++;
        }
    }

    if (count >= capacity) {
        capacity += 1;
        char **temp = realloc(result, capacity * sizeof(char *));
        if (temp == NULL) {
            goto cleanup;
        }
        result = temp;
    }
    result[count] = NULL;
    if (out_count != NULL) {
        *out_count = count;
    }
    regfree(&regex);
    return result;

cleanup:
    for (size_t i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
    regfree(&regex);
    return NULL;
}

int main(void) {
    const char *str = "Hello, world! This;is a test.";
    const char *pattern = "[, !;]+";
    size_t count = 0;
    char **tokens = split_string_regex(str, pattern, &count);

    if (tokens != NULL) {
        for (size_t i = 0; i < count; i++) {
            printf("Token %zu: %s\n", i, tokens[i]);
            free(tokens[i]);
        }
        free(tokens);
    }

    return 0;
}