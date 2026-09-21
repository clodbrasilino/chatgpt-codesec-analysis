#define _POSIX_C_SOURCE 200809L

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *str, size_t *count)
{
    if (count == NULL) {
        return NULL;
    }
    *count = 0;
    if (str == NULL || str[0] == '\0') {
        return NULL;
    }

    size_t str_len = strnlen(str, SIZE_MAX);

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t offset = 0;
    size_t split_count = 0;
    regmatch_t match;
    int rc;

    while ((rc = regexec(&regex, str + offset, 1, &match, 0)) == 0) {
        size_t abs_pos = offset + (size_t)match.rm_so;
        if (abs_pos > 0) {
            split_count++;
        }
        offset += (size_t)match.rm_eo;
    }

    if (rc != REG_NOMATCH) {
        regfree(&regex);
        return NULL;
    }

    size_t token_count = split_count + 1;
    char **result = malloc(token_count * sizeof(*result));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    offset = 0;
    size_t start = 0;
    size_t index = 0;

    while ((rc = regexec(&regex, str + offset, 1, &match, 0)) == 0) {
        size_t abs_pos = offset + (size_t)match.rm_so;
        if (abs_pos > 0) {
            size_t len = abs_pos - start;
            result[index] = strndup(str + start, len);
            if (result[index] == NULL) {
                for (size_t i = 0; i < index; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            index++;
            start = abs_pos;
        }
        offset += (size_t)match.rm_eo;
    }

    if (rc != REG_NOMATCH) {
        for (size_t i = 0; i < index; i++) {
            free(result[i]);
        }
        free(result);
        regfree(&regex);
        return NULL;
    }

    size_t len = str_len - start;
    result[index] = strndup(str + start, len);
    if (result[index] == NULL) {
        for (size_t i = 0; i < index; i++) {
            free(result[i]);
        }
        free(result);
        regfree(&regex);
        return NULL;
    }
    index++;

    *count = index;
    regfree(&regex);
    return result;
}

int main(void)
{
    size_t count = 0;
    char **parts = split_at_uppercase("HelloWorld", &count);
    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }
    for (size_t i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);
    return EXIT_SUCCESS;
}