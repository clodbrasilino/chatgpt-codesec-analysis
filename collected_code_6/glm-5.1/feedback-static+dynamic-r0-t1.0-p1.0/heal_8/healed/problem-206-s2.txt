#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** adjacent_concat(char** tuples, int size, int* result_size) {
    if (tuples == NULL || size <= 1 || result_size == NULL) {
        if (result_size != NULL) {
            *result_size = 0;
        }
        return NULL;
    }

    *result_size = size - 1;
    char** result = malloc(*result_size * sizeof(char*));
    if (result == NULL) {
        *result_size = 0;
        return NULL;
    }

    for (int i = 0; i < *result_size; i++) {
        if (tuples[i] == NULL || tuples[i + 1] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_size = 0;
            return NULL;
        }

        size_t len1 = strlen(tuples[i]);
        size_t len2 = strlen(tuples[i + 1]);

        size_t total_len = len1 + len2 + 1;
        
        if (total_len <= len1 || total_len <= len2) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_size = 0;
            return NULL;
        }

        result[i] = malloc(total_len);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_size = 0;
            return NULL;
        }

        memcpy(result[i], tuples[i], len1);
        memcpy(result[i] + len1, tuples[i + 1], len2);
        result[i][len1 + len2] = '\0';
    }

    return result;
}

void free_string_array(char** arr, int size) {
    if (arr == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main() {
    char* tuples[] = {"alpha", "beta", "gamma", "delta"};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int result_size = 0;

    char** result = adjacent_concat(tuples, size, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%s\n", result[i]);
        }
        free_string_array(result, result_size);
    }

    return 0;
}