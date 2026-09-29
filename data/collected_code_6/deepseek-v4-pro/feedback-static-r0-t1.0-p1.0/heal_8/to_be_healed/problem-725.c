#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **extract_quoted_values(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "\"([^\"]*)\"";
    char **results = NULL;
    size_t capacity = 0;
    size_t found = 0;

    if (str == NULL || count == NULL) {
        if (count) *count = 0;
        return NULL;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        *count = 0;
        return NULL;
    }

    const char *cursor = str;
    size_t str_len = 0;
    while (str[str_len] != '\0') str_len++;

    while (*cursor != '\0' && regexec(&regex, cursor, 2, matches, 0) == 0) {
        if (found >= capacity) {
            size_t new_capacity = capacity == 0 ? 4 : capacity * 2;
            char **new_results = realloc(results, new_capacity * sizeof(char *));
            if (!new_results) {
                for (size_t i = 0; i < found; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            results = new_results;
            capacity = new_capacity;
        }

        size_t start = matches[1].rm_so;
        size_t end = matches[1].rm_eo;
        size_t match_end = matches[0].rm_eo;

        if (start == (size_t)-1 || end == (size_t)-1 || match_end == (size_t)-1) {
            for (size_t i = 0; i < found; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        if (start >= str_len || end > str_len || end < start || match_end > str_len) {
            for (size_t i = 0; i < found; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        size_t substr_len = end - start;

        results[found] = malloc(substr_len + 1);
        if (!results[found]) {
            for (size_t i = 0; i < found; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        size_t src_offset = (size_t)(cursor - str) + start;
        if (src_offset + substr_len <= str_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(results[found], str + src_offset, substr_len);
        }
        results[found][substr_len] = '\0';
        found++;

        if (match_end == 0) {
            match_end = 1;
        }

        cursor += match_end;
    }

    regfree(&regex);
    *count = found;
    return results;
}

int main(void) {
    const char *test_string = "Hello \"world\" and \"universe\" with \"multiple words\"";
    size_t count = 0;
    char **values = extract_quoted_values(test_string, &count);

    if (values) {
        printf("Found %zu quoted values:\n", count);
        for (size_t i = 0; i < count; i++) {
            printf("[%zu] %s\n", i, values[i]);
            free(values[i]);
        }
        free(values);
    } else {
        printf("No quoted values found or error occurred\n");
    }

    const char *empty_string = "no quotes here";
    count = 0;
    values = extract_quoted_values(empty_string, &count);
    if (values) {
        for (size_t i = 0; i < count; i++) {
            free(values[i]);
        }
        free(values);
    }

    return 0;
}