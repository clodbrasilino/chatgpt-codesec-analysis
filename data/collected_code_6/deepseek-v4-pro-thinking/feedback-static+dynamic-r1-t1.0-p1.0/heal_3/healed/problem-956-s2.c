#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_at_uppercase(const char *str, size_t *count) {
    if (count == NULL) {
        return NULL;
    }
    *count = 0;
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t capacity = 8;
    size_t *starts = malloc(capacity * sizeof(size_t));
    if (starts == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t nstarts = 0;
    starts[nstarts++] = 0;

    const char *cursor = str;
    regmatch_t match;

    while (*cursor) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(starts);
            regfree(&regex);
            return NULL;
        }

        size_t pos = (size_t)(cursor - str) + match.rm_so;
        if (pos > 0) {
            if (nstarts >= capacity) {
                capacity *= 2;
                size_t *tmp = realloc(starts, capacity * sizeof(size_t));
                if (tmp == NULL) {
                    free(starts);
                    regfree(&regex);
                    return NULL;
                }
                starts = tmp;
            }
            starts[nstarts++] = pos;
        }

        size_t adv = (match.rm_eo == 0) ? 1 : match.rm_eo;
        cursor += adv;
    }

    regfree(&regex);

    char **result = malloc((nstarts + 1) * sizeof(char *));
    if (result == NULL) {
        free(starts);
        return NULL;
    }

    size_t total_len = (size_t)(cursor - str);
    size_t i;
    for (i = 0; i < nstarts; i++) {
        size_t start = starts[i];
        size_t end = (i + 1 < nstarts) ? starts[i + 1] : total_len;
        size_t seg_len = end - start;

        result[i] = malloc(seg_len + 1);
        if (result[i] == NULL) {
            size_t j;
            for (j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            free(starts);
            return NULL;
        }

        strncpy(result[i], str + start, seg_len);
        result[i][seg_len] = '\0';
    }

    result[nstarts] = NULL;
    free(starts);
    *count = nstarts;
    return result;
}

int main(void) {
    const char *input = "HelloWorldHowAreYou";
    size_t count = 0;
    char **parts = split_at_uppercase(input, &count);

    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return EXIT_FAILURE;
    }

    size_t i;
    for (i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }

    free(parts);
    return EXIT_SUCCESS;
}