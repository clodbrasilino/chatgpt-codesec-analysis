#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char **split_at_uppercase(const char *input, int *count) {
    regex_t regex;
    regmatch_t matches[1];
    const char *pattern = "[A-Z]";
    char **result = NULL;
    int capacity = 0;
    int start = 0;
    int i = 0;
    size_t len;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    len = strnlen(input, 4096);

    *count = 0;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return NULL;
    }

    result = malloc(sizeof(char *));
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }
    capacity = 1;

    while (i < (int)len) {
        if (regexec(&regex, input + i, 1, matches, 0) == 0) {
            int match_pos = i + matches[0].rm_so;
            int segment_len = match_pos - start;

            /* Possible weaknesses found:
             *  Assuming that condition 'segment_len>0' is not redundant
             */
            if (segment_len > 0) {
                if (*count >= capacity) {
                    int new_capacity = capacity * 2;
                    char **temp = realloc(result, new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        regfree(&regex);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }

                /* Possible weaknesses found:
                 *  Condition 'segment_len<0' is always false [knownConditionTrueFalse]
                 *  Condition 'segment_len<0' is always false
                 */
                if (segment_len < 0 || (size_t)segment_len > len - start) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }

                result[*count] = malloc(segment_len + 1);
                if (result[*count] == NULL) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    regfree(&regex);
                    return NULL;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[*count], input + start, segment_len);
                result[*count][segment_len] = '\0';
                (*count)++;
            }

            start = match_pos;
            i = match_pos + 1;
        } else {
            i++;
        }
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'start<(int)len' is not redundant
     */
    if (start < (int)len) {
        /* Possible weaknesses found:
         *  Assignment 'segment_len=(int)len-start', assigned value is greater than 0
         */
        int segment_len = (int)len - start;

        /* Possible weaknesses found:
         *  Condition 'segment_len<0' is always false [knownConditionTrueFalse]
         *  Condition 'segment_len<0' is always false
         */
        if (segment_len < 0 || (size_t)segment_len > len - start) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }

        if (*count >= capacity) {
            int new_capacity = capacity * 2;
            char **temp = realloc(result, new_capacity * sizeof(char *));
            if (temp == NULL) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                regfree(&regex);
                return NULL;
            }
            result = temp;
            /* Possible weaknesses found:
             *  Value stored to 'capacity' is never read [deadcode.DeadStores]
             *  Variable 'capacity' is assigned a value that is never used. [unreadVariable]
             */
            capacity = new_capacity;
        }

        result[*count] = malloc(segment_len + 1);
        if (result[*count] == NULL) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            regfree(&regex);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[*count], input + start, segment_len);
        result[*count][segment_len] = '\0';
        (*count)++;
    }

    regfree(&regex);
    return result;
}

int main(void) {
    const char *test_string = "helloWorldExample";
    int count = 0;
    char **parts = split_at_uppercase(test_string, &count);

    if (parts == NULL) {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}