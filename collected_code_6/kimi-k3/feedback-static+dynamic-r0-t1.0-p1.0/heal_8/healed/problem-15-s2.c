#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_lowercase(const char *str, size_t str_len, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    if (str_len == 0) {
        *count = 0;
        return NULL;
    }

    char **result = malloc((str_len + 1) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t start = 0;
    size_t idx = 0;

    for (size_t i = 0; i <= str_len; i++) {
        if (str[i] == '\0' || islower((unsigned char)str[i])) {
            size_t segment_len = i - start;
            if (segment_len > 0) {
                if (segment_len >= SIZE_MAX - 1) {
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

                if (segment_len <= str_len - start) {
                    if (segment_len > 0 && start + segment_len <= str_len) {
                        memcpy(result[idx], str + start, segment_len);
                        result[idx][segment_len] = '\0';
                        idx++;
                    } else {
                        free(result[idx]);
                        for (size_t j = 0; j < idx; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                } else {
                    free(result[idx]);
                    for (size_t j = 0; j < idx; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
            }
            start = i + 1;
        }
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
    size_t input_len = 0;
    
    if (input != NULL) {
        input_len = strlen(input);
    }
    
    int count = 0;

    char **segments = split_at_lowercase(input, input_len, &count);

    if (segments == NULL && count > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("Input: %s\n", input);
    printf("Segments found: %d\n", count);

    for (int i = 0; i < count; i++) {
        printf("Segment %d: %s\n", i + 1, segments[i]);
    }

    free_split_result(segments, count);

    return EXIT_SUCCESS;
}