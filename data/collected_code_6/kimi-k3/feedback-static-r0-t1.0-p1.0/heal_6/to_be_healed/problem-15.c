#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <limits.h>

#define MAX_INPUT_LEN 1024

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, MAX_INPUT_LEN);
    if (len == 0) {
        *count = 0;
        return NULL;
    }

    size_t max_splits = 1;
    for (size_t i = 0; i < len; i++) {
        if (islower((unsigned char)str[i])) {
            max_splits++;
        }
    }

    if (max_splits > SIZE_MAX / sizeof(char *)) {
        return NULL;
    }

    char **result = malloc(max_splits * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t start = 0;
    size_t idx = 0;

    for (size_t i = 0; i <= len; i++) {
        if (str[i] == '\0' || islower((unsigned char)str[i])) {
            size_t segment_len = i - start;
            
            if (segment_len == SIZE_MAX || segment_len >= MAX_INPUT_LEN) {
                for (size_t j = 0; j < idx; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            
            result[idx] = malloc(segment_len + 1);
            if (result[idx] == NULL) {
                for (size_t j = 0; j < idx; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            
            if (segment_len > 0) {
                /* Possible weaknesses found:
                 *  'copy_len' is assigned value 'segment_len' here.
                 */
                size_t copy_len = segment_len;
                /* Possible weaknesses found:
                 *  The comparison 'copy_len > segment_len' is always false because 'copy_len' and 'segment_len' represent the same value. [knownConditionTrueFalse]
                 *  The comparison 'copy_len > segment_len' is always false because 'copy_len' and 'segment_len' represent the same value.
                 */
                if (copy_len > segment_len) {
                    copy_len = segment_len;
                }
                if (copy_len >= segment_len + 1) {
                    copy_len = segment_len;
                }
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result[idx], str + start, copy_len);
            }
            result[idx][segment_len] = '\0';
            idx++;
            start = i;
        }
    }

    if (idx > INT_MAX) {
        for (size_t j = 0; j < idx; j++) {
            free(result[j]);
        }
        free(result);
        return NULL;
    }

    *count = (int)idx;
    return result;
}

void free_split_result(char **result, int count) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char *input = "HelloWorldThisIsATest";
    int count = 0;

    char **segments = split_at_lowercase(input, &count);

    if (segments == NULL && count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", input);
    printf("Segments (%d):\n", count);
    for (int i = 0; i < count; i++) {
        printf("[%d]: \"%s\"\n", i, segments[i]);
    }

    free_split_result(segments, count);

    return EXIT_SUCCESS;
}