#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strnlen(str, 1024);
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

            if (segment_len == SIZE_MAX) {
                for (size_t j = 0; j < idx; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }

            if (segment_len + 1 > SIZE_MAX) {
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
                if (segment_len > len - start) {
                    free(result[idx]);
                    for (size_t j = 0; j < idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                if (segment_len + 1 > segment_len) {
                    memcpy(result[idx], str + start, segment_len);
                }
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