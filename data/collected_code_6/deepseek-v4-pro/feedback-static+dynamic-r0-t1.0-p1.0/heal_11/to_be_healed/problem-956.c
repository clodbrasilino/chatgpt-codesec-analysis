#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

char **split_uppercase(const char *input, int *count) {
    char **result = NULL;
    int capacity = 16;
    size_t len;
    char *temp = NULL;
    size_t last_end = 0;
    size_t i;
    size_t segment_len;
    char **new_result;
    size_t j;

    if (!input || !count) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(input);
    if (len >= SIZE_MAX) {
        return NULL;
    }

    if (len == 0) {
        *count = 0;
        result = malloc((size_t)capacity * sizeof(char *));
        if (!result) {
            return NULL;
        }
        return result;
    }

    temp = malloc(len + 1);
    if (!temp) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp, input, len + 1);

    *count = 0;
    result = malloc((size_t)capacity * sizeof(char *));
    if (!result) {
        free(temp);
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            if (i > 0) {
                if (*count >= capacity) {
                    if (capacity > INT_MAX / 2) {
                        for (j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    capacity *= 2;
                    new_result = realloc(result, (size_t)capacity * sizeof(char *));
                    if (!new_result) {
                        for (j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    result = new_result;
                }

                segment_len = i - last_end;
                if (segment_len == 0) {
                    for (j = 0; j < (size_t)*count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    free(temp);
                    return NULL;
                }

                result[*count] = malloc(segment_len + 1);
                if (!result[*count]) {
                    for (j = 0; j < (size_t)*count; j++) {
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

    if (last_end < len) {
        if (*count >= capacity) {
            if (capacity > INT_MAX / 2) {
                for (j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            capacity *= 2;
            new_result = realloc(result, (size_t)capacity * sizeof(char *));
            if (!new_result) {
                for (j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            result = new_result;
        }

        segment_len = len - last_end;

        result[*count] = malloc(segment_len + 1);
        if (!result[*count]) {
            for (j = 0; j < (size_t)*count; j++) {
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