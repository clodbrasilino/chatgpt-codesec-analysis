#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **extract_quoted_values(const char *str, size_t *count) {
    regex_t regex;
    regmatch_t matches[2];
    const char *pattern = "\"([^\"]*)\"";
    const char *cursor = str;
    char **results = NULL;
    size_t capacity = 0;
    size_t found = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        *count = 0;
        return NULL;
    }

    while (regexec(&regex, cursor, 2, matches, 0) == 0) {
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

        if (start == (size_t)-1 || end == (size_t)-1 || end < start) {
            for (size_t i = 0; i < found; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         *  Same expression on both sides of '-'. [duplicateExpression]
         */
        if (start + (cursor - cursor) > (size_t)(cursor + matches[0].rm_eo - cursor) ||
            end > (size_t)matches[0].rm_eo) {
            for (size_t i = 0; i < found; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        size_t len = end - start;
        /* Possible weaknesses found:
         *  dest_size is assigned 'len+1' here.
         */
        size_t dest_size = len + 1;

        results[found] = malloc(dest_size);
        /* Possible weaknesses found:
         *  Assuming condition is false
         */
        if (!results[found]) {
            for (size_t i = 0; i < found; i++) {
                free(results[i]);
            }
            free(results);
            regfree(&regex);
            *count = 0;
            return NULL;
        }

        if (len > 0) {
            /* Possible weaknesses found:
             *  Condition 'dest_size<len+1' is always false [knownConditionTrueFalse]
             *  Condition 'dest_size<len+1' is always false
             */
            if (dest_size < len + 1) {
                free(results[found]);
                for (size_t i = 0; i < found; i++) {
                    free(results[i]);
                }
                free(results);
                regfree(&regex);
                *count = 0;
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(results[found], cursor + start, len);
        }
        results[found][len] = '\0';
        found++;

        cursor += matches[0].rm_eo;
        if (matches[0].rm_eo == 0) {
            cursor++;
        }
        if (*cursor == '\0') {
            break;
        }
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