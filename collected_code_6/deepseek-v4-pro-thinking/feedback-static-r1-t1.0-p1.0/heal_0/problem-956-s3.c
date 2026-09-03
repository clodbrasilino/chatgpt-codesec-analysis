#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <limits.h>

char **split_at_uppercase(const char *input, int *count)
{
    if (count == NULL) {
        return NULL;
    }
    *count = 0;
    if (input == NULL) {
        return NULL;
    }

    regex_t regex;
    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return NULL;
    }

    size_t len = strlen(input);
    size_t cap = 8;
    size_t *positions = malloc(cap * sizeof(*positions));
    if (positions == NULL) {
        regfree(&regex);
        return NULL;
    }

    size_t n = 0;
    size_t offset = 0;
    regmatch_t match;

    while (offset <= len) {
        int ret = regexec(&regex, input + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(positions);
            regfree(&regex);
            return NULL;
        }

        size_t pos = offset + (size_t)match.rm_so;

        if (n == cap) {
            cap *= 2;
            size_t *tmp = realloc(positions, cap * sizeof(*positions));
            if (tmp == NULL) {
                free(positions);
                regfree(&regex);
                return NULL;
            }
            positions = tmp;
        }

        positions[n++] = pos;

        if (match.rm_eo <= match.rm_so) {
            break;
        }
        offset = pos + 1;
        if (offset > len) {
            break;
        }
    }

    size_t start = 0;
    size_t token_count = 0;
    for (size_t i = 0; i < n; i++) {
        if (positions[i] == start && start == 0) {
            continue;
        }
        token_count++;
        start = positions[i];
    }
    token_count++;

    if (token_count > INT_MAX) {
        free(positions);
        regfree(&regex);
        return NULL;
    }

    char **result = malloc((token_count + 1) * sizeof(*result));
    if (result == NULL) {
        free(positions);
        regfree(&regex);
        return NULL;
    }

    start = 0;
    size_t idx = 0;
    for (size_t i = 0; i < n; i++) {
        size_t pos = positions[i];
        if (pos == start && start == 0) {
            continue;
        }

        size_t seg_len = pos - start;
        char *segment = malloc(seg_len + 1);
        if (segment == NULL) {
            for (size_t j = 0; j < idx; j++) {
                free(result[j]);
            }
            free(result);
            free(positions);
            regfree(&regex);
            return NULL;
        }

        memcpy(segment, input + start, seg_len);
        segment[seg_len] = '\0';
        result[idx++] = segment;
        start = pos;
    }

    size_t seg_len = len - start;
    char *segment = malloc(seg_len + 1);
    if (segment == NULL) {
        for (size_t j = 0; j < idx; j++) {
            free(result[j]);
        }
        free(result);
        free(positions);
        regfree(&regex);
        return NULL;
    }
    memcpy(segment, input + start, seg_len);
    segment[seg_len] = '\0';
    result[idx++] = segment;
    result[idx] = NULL;

    free(positions);
    regfree(&regex);
    *count = (int)token_count;
    return result;
}

int main(void)
{
    const char *text = "HelloWorldExample";
    int count = 0;
    char **parts = split_at_uppercase(text, &count);

    if (parts == NULL) {
        fprintf(stderr, "Error splitting string\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
    }

    for (int i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);

    return EXIT_SUCCESS;
}