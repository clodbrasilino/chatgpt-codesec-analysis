#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_string(const char *str, const char *pattern, int *count) {
    regex_t regex;
    regmatch_t match;
    char **result = NULL;
    char **temp = NULL;
    const char *cursor = str;
    size_t capacity = 10;
    size_t size = 0;
    size_t start = 0;
    size_t end;
    size_t len;

    if (str == NULL || pattern == NULL || count == NULL) {
        return NULL;
    }

    *count = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    while (*cursor != '\0') {
        if (regexec(&regex, cursor, 1, &match, 0) == 0) {
            end = start + (size_t)match.rm_so;
            
            /* Possible weaknesses found:
             *  Assuming that condition 'end>start' is not redundant
             */
            if (end > start) {
                if (size >= capacity) {
                    capacity *= 2;
                    temp = realloc(result, capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (size_t i = 0; i < size; i++) {
                            free(result[i]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                }

                /* Possible weaknesses found:
                 *  Assignment 'len=end-start', assigned value is greater than 0
                 */
                len = end - start;
                result[size] = malloc(len + 1);
                /* Possible weaknesses found:
                 *  Assuming condition is false
                 */
                if (result[size] == NULL) {
                    for (size_t i = 0; i < size; i++) {
                        free(result[i]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }

                /* Possible weaknesses found:
                 * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
                 *  Condition 'len>0' is always true [knownConditionTrueFalse]
                 *  Condition 'len>0' is always true
                 */
                if (len > 0 && len <= strlen(str + start)) {
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[size], str + start, len);
                    result[size][len] = '\0';
                    size++;
                } else {
                    free(result[size]);
                }
            }

            start = start + (size_t)match.rm_eo;
            cursor = str + start;
        } else {
            break;
        }
    }

    if (*cursor != '\0') {
        len = 0;
        while (cursor[len] != '\0') {
            len++;
        }
        
        if (size >= capacity) {
            capacity++;
            temp = realloc(result, capacity * sizeof(char *));
            if (temp == NULL) {
                for (size_t i = 0; i < size; i++) {
                    free(result[i]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
        }

        result[size] = malloc(len + 1);
        if (result[size] == NULL) {
            for (size_t i = 0; i < size; i++) {
                free(result[i]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[size], cursor, len);
        }
        result[size][len] = '\0';
        size++;
    }

    regfree(&regex);
    *count = (int)size;
    return result;
}

void free_split_result(char **result, int count) {
    if (result != NULL) {
        for (int i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char *input = "apple,banana;orange:grape|mango";
    const char *pattern = "[,;:|]";
    int count = 0;
    char **tokens = split_string(input, pattern, &count);

    if (tokens != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", tokens[i]);
        }
        free_split_result(tokens, count);
    }

    return 0;
}