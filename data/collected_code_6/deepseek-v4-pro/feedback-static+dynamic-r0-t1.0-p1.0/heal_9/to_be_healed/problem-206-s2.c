#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char** adjacent_concatenation(char** tuples, int tuple_count, int tuple_size) {
    if (tuples == NULL || tuple_count <= 0 || tuple_size <= 1) {
        return NULL;
    }

    size_t result_size = (size_t)tuple_count * (size_t)(tuple_size - 1);
    if (result_size > SIZE_MAX / sizeof(char*)) {
        return NULL;
    }

    char** result = (char**)malloc(result_size * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    int result_index = 0;
    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i * tuple_size] == NULL) {
            for (int j = 0; j < result_index; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        for (int j = 0; j < tuple_size - 1; j++) {
            char* str1 = tuples[i * tuple_size + j];
            char* str2 = tuples[i * tuple_size + j + 1];

            if (str1 == NULL || str2 == NULL || str1[0] == '\0' || str2[0] == '\0') {
                for (int k = 0; k < result_index; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len1 = strlen(str1);
            /* Possible weaknesses found:
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             */
            size_t len2 = strlen(str2);

            if (len1 > SIZE_MAX - len2 - 1) {
                for (int k = 0; k < result_index; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }

            size_t total_len = len1 + len2;

            result[result_index] = (char*)malloc(total_len + 1);
            if (result[result_index] == NULL) {
                for (int k = 0; k < result_index; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }

            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[result_index], str1, len1);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result[result_index] + len1, str2, len2 + 1);
            result_index++;
        }
    }

    return result;
}

int main(void) {
    char* tuples[3][3] = {
        {"ab", "cd", "ef"},
        {"gh", "ij", "kl"},
        {"mn", "op", "qr"}
    };

    int tuple_count = 3;
    int tuple_size = 3;

    size_t flattened_size = (size_t)tuple_count * (size_t)tuple_size;
    if (flattened_size > SIZE_MAX / sizeof(char*)) {
        return 1;
    }

    char** flattened = (char**)malloc(flattened_size * sizeof(char*));
    if (flattened == NULL) {
        return 1;
    }

    for (int i = 0; i < tuple_count; i++) {
        for (int j = 0; j < tuple_size; j++) {
            flattened[i * tuple_size + j] = tuples[i][j];
        }
    }

    char** result = adjacent_concatenation(flattened, tuple_count, tuple_size);
    if (result == NULL) {
        free(flattened);
        return 1;
    }

    int result_count = tuple_count * (tuple_size - 1);
    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);
    free(flattened);

    return 0;
}