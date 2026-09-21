#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char **split_uppercase(const char *input, int *count) {
    char **result = NULL;
    int capacity = 16;
    size_t len = 0;
    char *temp = NULL;
    size_t last_end = 0;
    size_t i;

    if (!input || !count) {
        return NULL;
    }

    while (input[len] != '\0') {
        if (len == SIZE_MAX) {
            return NULL;
        }
        len++;
    }

    if (len == 0) {
        *count = 0;
        result = malloc((size_t)capacity * sizeof(char *));
        if (!result) {
            return NULL;
        }
        return result;
    }

    if (len >= SIZE_MAX) {
        return NULL;
    }

    temp = malloc(len + 1);
    if (!temp) {
        return NULL;
    }

    memcpy(temp, input, len);
    temp[len] = '\0';

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
                    char **new_result;
                    if (capacity > INT_MAX / 2) {
                        size_t j;
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
                        size_t j;
                        for (j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    result = new_result;
                }

                {
                    size_t segment_len = i - last_end;
                    if (segment_len == 0) {
                        size_t j;
                        for (j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }

                    if (segment_len > len) {
                        size_t j;
                        for (j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }

                    result[*count] = malloc(segment_len + 1);
                    if (!result[*count]) {
                        size_t j;
                        for (j = 0; j < (size_t)*count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }

                    if (segment_len > 0) {
                        memcpy(result[*count], temp + last_end, segment_len);
                    }
                    result[*count][segment_len] = '\0';
                    (*count)++;
                    last_end = i;
                }
            }
        }
    }

    if (last_end < len) {
        if (*count >= capacity) {
            char **new_result;
            if (capacity > INT_MAX / 2) {
                size_t j;
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
                size_t j;
                for (j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            result = new_result;
        }

        {
            size_t segment_len = len - last_end;

            if (segment_len > len) {
                size_t j;
                for (j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }

            result[*count] = malloc(segment_len + 1);
            if (!result[*count]) {
                size_t j;
                for (j = 0; j < (size_t)*count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }

            if (segment_len > 0) {
                memcpy(result[*count], temp + last_end, segment_len);
            }
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