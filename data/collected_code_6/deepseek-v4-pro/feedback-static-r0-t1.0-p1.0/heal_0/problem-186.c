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

    regex_t regex;
    char pattern[1024];
    size_t pattern_len = 0;
    int ret;

    pattern[0] = '\0';

    for (size_t i = 0; i < literal_count; i++) {
        if (!literals[i]) {
            if (pattern_len > 0) {
                regfree(&regex);
            }
            return -1;
        }

        size_t lit_len = strlen(literals[i]);
        if (lit_len == 0) {
            if (pattern_len > 0) {
                regfree(&regex);
            }
            return -1;
        }

        if (i > 0) {
            if (pattern_len + 1 >= sizeof(pattern)) {
                if (pattern_len > 0) {
                    regfree(&regex);
                }
                return -1;
            }
            pattern[pattern_len++] = '|';
            pattern[pattern_len] = '\0';
        }

        pattern[pattern_len++] = '(';
        if (pattern_len >= sizeof(pattern)) {
            if (pattern_len > 0) {
                regfree(&regex);
            }
            return -1;
        }
        pattern[pattern_len] = '\0';

        for (size_t j = 0; j < lit_len; j++) {
            if (strchr(".[]{}()*+-?^$|\\", literals[i][j])) {
                if (pattern_len + 1 >= sizeof(pattern)) {
                    if (pattern_len > 0) {
                        regfree(&regex);
                    }
                    return -1;
                }
                pattern[pattern_len++] = '\\';
                pattern[pattern_len] = '\0';
            }

            if (pattern_len + 1 >= sizeof(pattern)) {
                if (pattern_len > 0) {
                    regfree(&regex);
                }
                return -1;
            }
            pattern[pattern_len++] = literals[i][j];
            pattern[pattern_len] = '\0';
        }

        if (pattern_len + 1 >= sizeof(pattern)) {
            if (pattern_len > 0) {
                regfree(&regex);
            }
            return -1;
        }
        pattern[pattern_len++] = ')';
        pattern[pattern_len] = '\0';
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    size_t max_matches = strlen(input) + 1;
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

        size_t match_len = pmatch[0].rm_eo - pmatch[0].rm_so;
        if (match_len == 0) {
            match_len = 1;
        }

        cursor += pmatch[0].rm_eo;
        offset += pmatch[0].rm_eo;
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