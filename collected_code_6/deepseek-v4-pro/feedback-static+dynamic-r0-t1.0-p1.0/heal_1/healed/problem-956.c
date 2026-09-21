#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_uppercase(const char *input, int *count) {
    char **result = NULL;
    int capacity = 16;
    int len = 0;
    char *temp = NULL;
    char *current = NULL;
    int last_end = 0;
    int i;

    if (!input || !count) {
        return NULL;
    }

    len = strlen(input);
    if (len == 0) {
        *count = 0;
        result = malloc(capacity * sizeof(char *));
        return result;
    }

    temp = strdup(input);
    if (!temp) {
        return NULL;
    }
    current = temp;

    *count = 0;
    result = malloc(capacity * sizeof(char *));
    if (!result) {
        free(temp);
        return NULL;
    }

    for (i = 0; i < len; i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            if (i > 0) {
                if (*count >= capacity) {
                    char **new_result;
                    capacity *= 2;
                    new_result = realloc(result, capacity * sizeof(char *));
                    if (!new_result) {
                        int j;
                        for (j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    result = new_result;
                }

                {
                    int segment_len = i - last_end;
                    result[*count] = malloc(segment_len + 1);
                    if (!result[*count]) {
                        int j;
                        for (j = 0; j < *count; j++) {
                            free(result[j]);
                        }
                        free(result);
                        free(temp);
                        return NULL;
                    }
                    memcpy(result[*count], current + last_end, segment_len);
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
            capacity *= 2;
            new_result = realloc(result, capacity * sizeof(char *));
            if (!new_result) {
                int j;
                for (j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            result = new_result;
        }

        {
            int segment_len = len - last_end;
            result[*count] = malloc(segment_len + 1);
            if (!result[*count]) {
                int j;
                for (j = 0; j < *count; j++) {
                    free(result[j]);
                }
                free(result);
                free(temp);
                return NULL;
            }
            memcpy(result[*count], current + last_end, segment_len);
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