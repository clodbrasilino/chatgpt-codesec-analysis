#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static char **split_uppercase(const char *input, int *count) {
    int capacity = 16;
    char **result;
    size_t len;

    if (!input || !count) {
        return NULL;
    }

    len = strlen(input);
    if (len == 0) {
        *count = 0;
        result = malloc(sizeof(char *));
        if (!result) {
            return NULL;
        }
        result[0] = NULL;
        return result;
    }

    result = malloc((size_t)capacity * sizeof(char *));
    if (!result) {
        return NULL;
    }

    *count = 0;
    size_t last_end = 0;

    for (size_t i = 0; i < len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            if (i > 0) {
                if (*count >= capacity) {
                    int new_capacity = capacity * 2;
                    if (new_capacity < capacity) {
                        for (int j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    char **new_result = realloc(result, (size_t)new_capacity * sizeof(char *));
                    if (!new_result) {
                        for (int j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        return NULL;
                    }
                    result = new_result;
                    capacity = new_capacity;
                }

                size_t segment_len = i - last_end;
                result[*count] = malloc(segment_len + 1);
                if (!result[*count]) {
                    for (int j = 0; j < *count; j++) {
                        free(result[j]);
                    }
                    free(result);
                    return NULL;
                }
                memcpy(result[*count], input + last_end, segment_len);
                result[*count][segment_len] = '\0';
                (*count)++;
                last_end = i;
            }
        }
    }

    if (last_end < len) {
        if (*count >= capacity) {
            int new_capacity = capacity * 2;
            if (new_capacity < capacity) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            char **new_result = realloc(result, (size_t)new_capacity * sizeof(char *));
            if (!new_result) {
                for (int j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                return NULL;
            }
            result = new_result;
            capacity = new_capacity;
        }

        size_t segment_len = len - last_end;
        result[*count] = malloc(segment_len + 1);
        if (!result[*count]) {
            for (int j = 0; j < *count; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }
        memcpy(result[*count], input + last_end, segment_len);
        result[*count][segment_len] = '\0';
        (*count)++;
    }

    return result;
}

static void free_split_result(char **result, int count) {
    if (result) {
        for (int i = 0; i < count; i++) {
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
        printf("Original: %s\n", test_string);
        printf("Split into %d parts:\n", count);
        for (int i = 0; i < count; i++) {
            printf("  [%d]: %s\n", i, parts[i]);
        }
        free_split_result(parts, count);
    } else {
        fprintf(stderr, "Failed to split string\n");
        return 1;
    }

    return 0;
}