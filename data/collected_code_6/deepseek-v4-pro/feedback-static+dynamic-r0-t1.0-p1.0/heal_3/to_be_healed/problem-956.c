#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_uppercase(const char *input, int *count) {
    char **result = NULL;
    int capacity = 16;
    int len = 0;
    char *temp = NULL;
    int last_end = 0;
    int i;

    if (!input || !count) {
        return NULL;
    }

    len = 0;
    while (input[len] != '\0') {
        len++;
        if (len < 0) {
            return NULL;
        }
    }

    if (len == 0) {
        *count = 0;
        result = malloc(capacity * sizeof(char *));
        return result;
    }

    temp = malloc(len + 1);
    if (!temp) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, input, len);
    temp[len] = '\0';

    *count = 0;
    result = malloc(capacity * sizeof(char *));
    if (!result) {
        free(temp);
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            if (i > 0) {
                if (*count >= capacity) {
                    char **new_result;
                    capacity *= 2;
                    if (capacity < 0) {
                        int j;
                        for (j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    new_result = realloc(result, capacity * sizeof(char *));
                    if (!new_result) {
                        int j;
                        for (j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    result = new_result;
                }

                {
                    int segment_len = i - last_end;
                    if (segment_len < 0) {
                        int j;
                        for (j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    result[*count] = malloc(segment_len + 1);
                    if (!result[*count]) {
                        int j;
                        for (j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(result[*count], temp + last_end, segment_len);
                    result[*count][segment_len] = '\0';
                    (*count)++;
                    last_end = i;
                }
            }
        }
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'last_end<len' is not redundant
     */
    if (last_end < len) {
        if (*count >= capacity) {
            char **new_result;
            capacity *= 2;
            if (capacity < 0) {
                int j;
                for (j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            new_result = realloc(result, capacity * sizeof(char *));
            if (!new_result) {
                int j;
                for (j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            result = new_result;
        }

        {
            /* Possible weaknesses found:
             *  Assignment 'segment_len=len-last_end', assigned value is greater than 0
             */
            int segment_len = len - last_end;
            /* Possible weaknesses found:
             *  Condition 'segment_len<0' is always false
             *  Condition 'segment_len<0' is always false [knownConditionTrueFalse]
             */
            if (segment_len < 0) {
                int j;
                for (j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            result[*count] = malloc(segment_len + 1);
            if (!result[*count]) {
                int j;
                for (j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[*count], temp + last_end, segment_len);
            result[*count][segment_len] = '\0';
            (*count)++;
        }
    }

    free(temp);
    return result;
}

void free_split_result(char **result, int count) {
    if (result) {
        int i;
        for (i = 0; i < count; i++) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_uppercase(test_string, &count);

    if (parts) {
        int i;
        printf("Original: %s\n", test_string);
        printf("Split into %d parts:\n", count);
        for (i = 0; i < count; i++) {
            printf("  [%d]: %s\n", i, parts[i]);
        }
        free_split_result(parts, count);
    } else {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    return 0;
}