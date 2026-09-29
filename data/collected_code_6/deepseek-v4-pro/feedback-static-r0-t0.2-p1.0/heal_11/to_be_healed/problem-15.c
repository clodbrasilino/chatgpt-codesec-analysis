#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, 1024);
    if (len == 1024 && str[1024] != '\0') {
        return NULL;
    }

    if (len > SIZE_MAX - 1) {
        return NULL;
    }

    size_t capacity = 10;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t segment_start = 0;
    *count = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            size_t segment_len = i - segment_start;
            if (segment_len > 0) {
                if ((size_t)*count >= capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        for (int j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char **temp = realloc(result, new_capacity * sizeof(char *));
                    if (temp == NULL) {
                        for (int j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = temp;
                    capacity = new_capacity;
                }

                if (segment_len > SIZE_MAX - 1) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                char *segment = malloc(segment_len + 1);
                if (segment == NULL) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                if (segment_len > 0) {
                    size_t remaining = len - segment_start;
                    /* Possible weaknesses found:
                     *  copy_len is assigned 'segment_len<remaining?segment_len:remaining' here.
                     */
                    size_t copy_len = segment_len < remaining ? segment_len : remaining;
                    /* Possible weaknesses found:
                     *  Condition 'copy_len>segment_len' is always true [knownConditionTrueFalse]
                     *  Condition 'copy_len>segment_len' is always true
                     */
                    if (copy_len > segment_len) {
                        free(segment);
                        for (int j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    /* Possible weaknesses found:
                     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                     */
                    memcpy(segment, str + segment_start, copy_len);
                }
                segment[segment_len] = '\0';
                result[*count] = segment;
                (*count)++;
            }
            segment_start = i + 1;
        }
    }

    if (*count == 0) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_lowercase(test_string, &count);

    if (parts == NULL) {
        printf("No segments found or error occurred\n");
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("%s\n", parts[i]);
        free(parts[i]);
    }
    free(parts);

    return 0;
}