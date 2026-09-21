#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_adjacent_tuples(char** tuples, const size_t* sizes, size_t count, size_t* result_count) {
    if (count < 2) {
        *result_count = 0;
        return NULL;
    }

    *result_count = count - 1;
    char** result = (char**)malloc(*result_count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < *result_count; i++) {
        size_t len1 = sizes[i];
        size_t len2 = sizes[i + 1];
        size_t total_len = len1 + len2;

        result[i] = (char*)malloc((total_len + 1) * sizeof(char));
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
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

int main() {
    const char* tuples[] = {"abc", "def", "gh", "ijk"};
    size_t sizes[] = {3, 3, 2, 3};
    size_t count = sizeof(sizes) / sizeof(sizes[0]);
    size_t result_count = 0;

    char** result = concatenate_adjacent_tuples((char**)tuples, sizes, count, &result_count);

    if (result != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}