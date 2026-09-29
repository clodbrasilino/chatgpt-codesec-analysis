#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **concat_adjacent(const char **tuples, size_t len, size_t *out_len) {
    if (tuples == NULL || len == 0 || out_len == NULL || len > SIZE_MAX - 1) {
        if (out_len != NULL) {
            *out_len = 0;
        }
        return NULL;
    }

    size_t result_len = (len + 1) / 2;
    if (result_len > SIZE_MAX / sizeof(char *)) {
        *out_len = 0;
        return NULL;
    }

    char **result = malloc(result_len * sizeof(char *));
    if (result == NULL) {
        *out_len = 0;
        return NULL;
    }

    for (size_t i = 0, j = 0; i < len; i += 2, j++) {
        if (tuples[i] == NULL) {
            for (size_t k = 0; k < j; k++) {
                free(result[k]);
            }
            free(result);
            *out_len = 0;
            return NULL;
        }

        size_t len1 = strnlen(tuples[i], SIZE_MAX);

        if (i + 1 < len) {
            if (tuples[i + 1] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                *out_len = 0;
                return NULL;
            }

            size_t len2 = strnlen(tuples[i + 1], SIZE_MAX);
            
            size_t combined_len = len1 + len2;
            if (combined_len < len1 || combined_len + 1 < combined_len) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                *out_len = 0;
                return NULL;
            }
            
            result[j] = malloc(combined_len + 1);
            if (result[j] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                *out_len = 0;
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[j], tuples[i], len1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[j] + len1, tuples[i + 1], len2);
            result[j][combined_len] = '\0';
        } else {
            /* Possible weaknesses found:
             *  total_len is assigned 'len1+1' here.
             */
            size_t total_len = len1 + 1;
            /* Possible weaknesses found:
             *  Condition 'total_len<len1' is always false
             *  Condition 'total_len<len1' is always false [knownConditionTrueFalse]
             */
            if (total_len < len1) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                *out_len = 0;
                return NULL;
            }
            
            result[j] = malloc(total_len);
            if (result[j] == NULL) {
                for (size_t k = 0; k < j; k++) {
                    free(result[k]);
                }
                free(result);
                *out_len = 0;
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[j], tuples[i], total_len);
        }
    }

    *out_len = result_len;
    return result;
}

int main(void) {
    const char *tuples[] = {"apple", "banana", "cherry", "date", "elderberry"};
    size_t len = sizeof(tuples) / sizeof(tuples[0]);
    size_t out_len = 0;

    char **result = concat_adjacent(tuples, len, &out_len);

    if (result != NULL) {
        for (size_t i = 0; i < out_len; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}