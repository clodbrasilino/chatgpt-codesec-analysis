#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *str, const char *pattern, size_t *count) {
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t capacity = 10;
    size_t idx = 0;
    char **result = NULL;
    const char *cursor = str;

    if (str == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = (char **)malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (1) {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t raw_len = strlen(cursor);
            if (raw_len > 0) {
                if (idx >= capacity) {
                    capacity *= 2;
                    char **tmp = (char **)realloc(result, capacity * sizeof(char *));
                    if (tmp == NULL) {
                        for (size_t i = 0; i < idx; i++) free(result[i]);
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = tmp;
                }
                /* Possible weaknesses found:
                 *  Assignment 'alloc_size=raw_len+1', assigned value is greater than 0
                 *  alloc_size is assigned 'raw_len+1' here.
                 */
                size_t alloc_size = raw_len + 1;
                result[idx] = (char *)malloc(alloc_size);
                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (result[idx] == NULL) {
                    for (size_t i = 0; i < idx; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 *  Condition 'alloc_size>0' is always true [knownConditionTrueFalse]
                 *  Condition 'raw_len<=alloc_size' is always true [knownConditionTrueFalse]
                 *  Condition 'raw_len<=alloc_size' is always true
                 *  Condition 'alloc_size>0' is always true
                 */
                if (alloc_size > 0 && raw_len <= alloc_size) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[idx], cursor, raw_len);
                }
                result[idx][raw_len] = '\0';
                idx++;
            }
            break;
        }

        if (match.rm_so > 0) {
            if (idx >= capacity) {
                capacity *= 2;
                char **tmp = (char **)realloc(result, capacity * sizeof(char *));
                if (tmp == NULL) {
                    for (size_t i = 0; i < idx; i++) free(result[i]);
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                result = tmp;
            }
            /* Possible weaknesses found:
             *  alloc_len is assigned '(unsigned long)match.rm_so+1' here.
             */
            size_t alloc_len = (size_t)match.rm_so + 1;
            result[idx] = (char *)malloc(alloc_len);
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (result[idx] == NULL) {
                for (size_t i = 0; i < idx; i++) free(result[i]);
                free(result);
                regfree(&regex);
                return NULL;
            }
            /* Possible weaknesses found:
             *  Condition '(unsigned long)match.rm_so<alloc_len' is always true
             *  Condition '(unsigned long)match.rm_so<alloc_len' is always true [knownConditionTrueFalse]
             */
            if (match.rm_so > 0 && (size_t)match.rm_so < alloc_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[idx], cursor, match.rm_so);
            }
            result[idx][match.rm_so] = '\0';
            idx++;
        }

        cursor += match.rm_eo;
        if (match.rm_so == match.rm_eo) {
            if (*cursor == '\0') {
                break;
            }
            cursor++;
        }
    }

    regfree(&regex);

    char **final_result = (char **)realloc(result, (idx + 1) * sizeof(char *));
    if (final_result != NULL) {
        result = final_result;
    }
    result[idx] = NULL;
    *count = idx;

    return result;
}

void free_split_result(char **result) {
    if (result == NULL) {
        return;
    }
    for (size_t i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *str = "Hello,world;this.is:a-test";
    const char *pattern = "[,;.: -]+";
    size_t count = 0;

    char **tokens = split_string(str, pattern, &count);
    if (tokens == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++) {
        printf("%s\n", tokens[i]);
    }

    free_split_result(tokens);

    return EXIT_SUCCESS;
}