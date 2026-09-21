#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

char **split_at_lowercase(const char *str, int *count) {
    if (str == NULL || count == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    size_t capacity = 10;
    char **result = malloc(capacity * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    size_t segment_start = 0;
    int segment_count = 0;

    for (size_t i = 0; i <= len; i++) {
        if (i == len || islower((unsigned char)str[i])) {
            size_t segment_len = i - segment_start;
            if (segment_len > 0) {
                char *segment = malloc(segment_len + 1);
                if (segment == NULL) {
                    for (int j = 0; j < segment_count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }

                memcpy(segment, str + segment_start, segment_len);
                segment[segment_len] = '\0';

                if (segment_count >= (int)capacity) {
                    size_t new_capacity = capacity * 2;
                    if (new_capacity > SIZE_MAX / sizeof(char *)) {
                        free(segment);
                        for (int j = 0; j < segment_count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char **new_result = realloc(result, new_capacity * sizeof(char *));
                    if (new_result == NULL) {
                        free(segment);
                        for (int j = 0; j < segment_count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    capacity = new_capacity;
                }

                result[segment_count++] = segment;
            }
            segment_start = i + 1;
        }
    }

    if (segment_count == 0) {
        free(result);
        *count = 0;
        return NULL;
    }

    *count = segment_count;
    return result;
}

int main(void) {
    const char *test_string = "HelloWorldThisIsATest";
    int count = 0;
    char **parts = split_at_lowercase(test_string, &count);

    if (parts != NULL) {
        for (int i = 0; i < count; i++) {
            printf("%s\n", parts[i]);
            free(parts[i]);
        }
        free(parts);
    } else {
        printf("No segments found or error occurred\n");
    }

    return 0;
}