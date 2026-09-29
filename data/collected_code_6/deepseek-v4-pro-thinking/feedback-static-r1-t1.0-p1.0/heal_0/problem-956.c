#define _POSIX_C_SOURCE 200112L

#include <stddef.h>
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

    regex_t regex;
    size_t str_len = strlen(str);
    size_t offset = 0;
    size_t split_count = 0;
    regmatch_t match;
    int rc;

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    while ((rc = regexec(&regex, str + offset, 1, &match, 0)) == 0) {
        size_t abs_pos = offset + (size_t)match.rm_so;

        if (abs_pos > 0) {
            split_count++;
        }

        offset = offset + (size_t)match.rm_eo;
        if (offset > str_len) {
            offset = str_len;
        }
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

            result[index] = malloc(len + 1);
            if (result[index] == NULL) {
                for (size_t i = 0; i < index; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }

            memcpy(result[index], str + start, len);
            result[index][len] = '\0';
            index++;
            start = abs_pos;
        }

        offset = offset + (size_t)match.rm_eo;
        if (offset > str_len) {
            offset = str_len;
        }
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
    result[index] = malloc(len + 1);

    if (result[index] == NULL) {
        for (size_t i = 0; i < index; i++) {
            free(result[i]);
        }
        free(result);
        regfree(&regex);
        return NULL;
    }

    memcpy(result[index], str + start, len);
    result[index][len] = '\0';
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