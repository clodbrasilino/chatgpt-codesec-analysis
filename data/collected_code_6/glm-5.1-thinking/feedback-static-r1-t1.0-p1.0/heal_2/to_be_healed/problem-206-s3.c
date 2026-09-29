#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char** adjacent_element_concatenation(const char** tuple, size_t count, size_t* out_count) {
    if (tuple == NULL || out_count == NULL) {
        if (out_count != NULL) {
            *out_count = 0;
        }
        return NULL;
    }

    if (count < 2) {
        *out_count = 0;
        return NULL;
    }

    size_t result_count = count - 1;
    char** result = (char**)malloc(result_count * sizeof(char*));
    if (result == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < result_count; i++) {
        const char* str1 = tuple[i] != NULL ? tuple[i] : "";
        const char* str2 = tuple[i + 1] != NULL ? tuple[i + 1] : "";

        size_t len1 = strnlen(str1, SIZE_MAX);
        size_t len2 = strnlen(str2, SIZE_MAX);

        result[i] = (char*)malloc(len1 + len2 + 1);
        if (result[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            *out_count = 0;
            return NULL;
        }

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i], str1, len1);
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result[i] + len1, str2, len2);
        result[i][len1 + len2] = '\0';
    }

    *out_count = result_count;
    return result;
}

void free_result(char** arr, size_t count) {
    if (arr == NULL) {
        return;
    }
    for (size_t i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}

int main(void) {
    const char* test_tuple[] = {"G", "F", "G", "I", "S", "B", "E", "S", "T"};
    size_t test_count = sizeof(test_tuple) / sizeof(test_tuple[0]);
    size_t out_count = 0;

    char** result = adjacent_element_concatenation(test_tuple, test_count, &out_count);

    if (result != NULL) {
        for (size_t i = 0; i < out_count; i++) {
            printf("%s ", result[i]);
        }
        printf("\n");
        free_result(result, out_count);
    }

    return 0;
}