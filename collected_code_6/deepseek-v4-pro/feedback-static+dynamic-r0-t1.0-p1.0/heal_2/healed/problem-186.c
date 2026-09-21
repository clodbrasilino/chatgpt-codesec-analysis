#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int search_literals(const char *input, const char **literals, size_t literal_count, int **matches, size_t *match_count) {
    if (!input || !literals || !matches || !match_count || literal_count == 0) {
        return -1;
    }

    *matches = NULL;
    *match_count = 0;

    size_t input_len = 0;
    while (input[input_len] != '\0') {
        input_len++;
    }
    if (input_len == 0) {
        return 0;
    }

    regex_t regex;
    size_t pattern_capacity = 1024;
    char *pattern = (char *)malloc(pattern_capacity);
    if (!pattern) {
        return -1;
    }
    size_t pattern_len = 0;
    pattern[0] = '\0';

    for (size_t i = 0; i < literal_count; i++) {
        if (!literals[i]) {
            free(pattern);
            return -1;
        }

        size_t lit_len = 0;
        while (literals[i][lit_len] != '\0') {
            lit_len++;
        }
        if (lit_len == 0) {
            free(pattern);
            return -1;
        }

        size_t needed = pattern_len;

        if (i > 0) {
            needed += 1;
        }
        needed += 1;
        for (size_t j = 0; j < lit_len; j++) {
            if (strchr(".[]{}()*+-?^$|\\", literals[i][j])) {
                needed += 2;
            } else {
                needed += 1;
            }
        }
        needed += 1;
        needed += 1;

        if (needed > pattern_capacity) {
            pattern_capacity = needed * 2;
            char *new_pattern = (char *)realloc(pattern, pattern_capacity);
            if (!new_pattern) {
                free(pattern);
                return -1;
            }
            pattern = new_pattern;
        }

        if (i > 0) {
            pattern[pattern_len++] = '|';
        }

        pattern[pattern_len++] = '(';

        for (size_t j = 0; j < lit_len; j++) {
            if (strchr(".[]{}()*+-?^$|\\", literals[i][j])) {
                pattern[pattern_len++] = '\\';
            }
            pattern[pattern_len++] = literals[i][j];
        }

        pattern[pattern_len++] = ')';
        pattern[pattern_len] = '\0';
    }

    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);
    if (ret != 0) {
        return -1;
    }

    size_t max_matches = input_len + 1;
    regmatch_t *pmatch = (regmatch_t *)malloc(max_matches * sizeof(regmatch_t));
    if (!pmatch) {
        regfree(&regex);
        return -1;
    }

    int *result = (int *)malloc(max_matches * sizeof(int));
    if (!result) {
        free(pmatch);
        regfree(&regex);
        return -1;
    }

    size_t count = 0;
    const char *cursor = input;
    int offset = 0;

    while (cursor[0] != '\0' && count < max_matches) {
        ret = regexec(&regex, cursor, 1, pmatch, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            free(result);
            free(pmatch);
            regfree(&regex);
            return -1;
        }

        result[count] = offset + pmatch[0].rm_so;

        size_t advance = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (advance == 0) {
            advance = 1;
        }

        cursor += advance;
        offset += advance;
        count++;
    }

    free(pmatch);
    regfree(&regex);

    if (count == 0) {
        free(result);
        *matches = NULL;
        *match_count = 0;
        return 0;
    }

    int *resized = (int *)realloc(result, count * sizeof(int));
    if (!resized) {
        free(result);
        return -1;
    }

    *matches = resized;
    *match_count = count;
    return 0;
}

int main(void) {
    const char *literals[] = {"foo", "bar", "baz"};
    int *matches = NULL;
    size_t match_count = 0;
    int ret;

    ret = search_literals("foo test bar and baz plus foo", literals, 3, &matches, &match_count);
    if (ret != 0) {
        fprintf(stderr, "Error during search\n");
        return 1;
    }

    printf("Found %zu matches:\n", match_count);
    for (size_t i = 0; i < match_count; i++) {
        printf("  Match at position %d\n", matches[i]);
    }

    free(matches);
    return 0;
}