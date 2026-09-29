#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char **split_at_uppercase(const char *input, int *count) {
    char **result = NULL;
    int capacity = 0;
    int size = 0;
    const char *cursor;

    if (input == NULL || count == NULL) {
        return NULL;
    }

    result = malloc(sizeof(char *));
    if (result == NULL) {
        return NULL;
    }
    capacity = 1;
    *count = 0;

    cursor = input;

    while (*cursor != '\0') {
        const char *start = cursor;
        const char *end = NULL;

        if (*cursor >= 'A' && *cursor <= 'Z') {
            cursor++;
            while (*cursor != '\0' && (*cursor >= 'a' && *cursor <= 'z')) {
                cursor++;
            }
            end = cursor;
        } else {
            while (*cursor != '\0' && !(*cursor >= 'A' && *cursor <= 'Z')) {
                cursor++;
            }
            end = cursor;
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'end>start' is not redundant
         */
        if (end > start) {
            /* Possible weaknesses found:
             *  Assignment 'len=(unsigned long)(end-start)', assigned value is greater than 0
             */
            size_t len = (size_t)(end - start);

            char *segment = malloc(len + 1);
            /* Possible weaknesses found:
             *  Assuming condition is false
             */
            if (segment == NULL) {
                for (int i = 0; i < size; i++) {
                    free(result[i]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             *  Condition 'len>0' is always true
             *  Condition 'len>0' is always true [knownConditionTrueFalse]
             */
            if (len > 0) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(segment, start, len);
            }
            segment[len] = '\0';

            if (size >= capacity) {
                if (capacity > SIZE_MAX / 2) {
                    free(segment);
                    for (int i = 0; i < size; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                size_t new_capacity = (size_t)capacity * 2;
                if (new_capacity > SIZE_MAX / sizeof(char *)) {
                    free(segment);
                    for (int i = 0; i < size; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                char **temp = realloc(result, new_capacity * sizeof(char *));
                if (temp == NULL) {
                    free(segment);
                    for (int i = 0; i < size; i++) {
                        free(result[i]);
                    }
                    free(result);
                    return NULL;
                }
                result = temp;
                capacity = (int)new_capacity;
            }
            result[size++] = segment;
        }
    }

    *count = size;
    return result;
}

int main(void) {
    const char *test_string = "helloWorldThisIsATest";
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