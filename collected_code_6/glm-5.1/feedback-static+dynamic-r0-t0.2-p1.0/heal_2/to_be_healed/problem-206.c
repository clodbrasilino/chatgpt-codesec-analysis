#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** adjacent_concat(const char** tuples, int size, int* result_size) {
    if (tuples == NULL || size < 0 || result_size == NULL) {
        return NULL;
    }

    if (size < 2) {
        *result_size = 0;
        return NULL;
    }

    *result_size = size - 1;
    char** result = (char**)malloc(*result_size * sizeof(char*));
    if (result == NULL) {
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

        size_t len1 = strnlen(tuples[i], SIZE_MAX);
        size_t len2 = strnlen(tuples[i + 1], SIZE_MAX);

        if (len1 > SIZE_MAX - len2 || len1 + len2 > SIZE_MAX - 1) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *result_size = 0;
            return NULL;
        }

        size_t total_len = len1 + len2;
        result[i] = (char*)malloc(total_len + 1);
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], tuples[i], len1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i] + len1, tuples[i + 1], len2);
        result[i][total_len] = '\0';
    }

    return result;
}

void free_result(char** result, int size) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < size; i++) {
        free(result[i]);
    }
    free(result);
}

int main() {
    const char* tuples[] = {"Alpha", "Beta", "Gamma", "Delta"};
    int size = sizeof(tuples) / sizeof(tuples[0]);
    int result_size = 0;

    char** result = adjacent_concat(tuples, size, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%s\n", result[i]);
        }
        free_result(result, result_size);
    }

    return 0;
}