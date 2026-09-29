#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** adjacent_concatenation(char** tuples, int tuple_count, int tuple_size) {
    if (tuples == NULL || tuple_count <= 0 || tuple_size <= 1) {
        return NULL;
    }

    size_t total_results = (size_t)tuple_count * (tuple_size - 1);
    char** result = (char**)malloc(total_results * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    size_t result_index = 0;
    for (int i = 0; i < tuple_count; i++) {
        if (tuples[i] == NULL) {
            for (size_t j = 0; j < result_index; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        for (int j = 0; j < tuple_size - 1; j++) {
            if (tuples[i * tuple_size + j] == NULL || tuples[i * tuple_size + j + 1] == NULL) {
                for (size_t k = 0; k < result_index; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }

            size_t len1 = strnlen(tuples[i * tuple_size + j], 4096);
            size_t len2 = strnlen(tuples[i * tuple_size + j + 1], 4096);
            size_t total_len = len1 + len2;
            
            result[result_index] = (char*)malloc((total_len + 1) * sizeof(char));
            if (result[result_index] == NULL) {
                for (size_t k = 0; k < result_index; k++) {
                    free(result[k]);
                }
                free(result);
                return NULL;
            }

            snprintf(result[result_index], total_len + 1, "%s%s", 
                     tuples[i * tuple_size + j], tuples[i * tuple_size + j + 1]);
            result_index++;
        }
    }

    return result;
}

int main(void) {
    const char* tuple_data[3][3] = {
        {"ab", "cd", "ef"},
        {"gh", "ij", "kl"},
        {"mn", "op", "qr"}
    };

    int tuple_count = 3;
    int tuple_size = 3;

    char** flattened = (char**)malloc((size_t)tuple_count * tuple_size * sizeof(char*));
    if (flattened == NULL) {
        return 1;
    }

    for (int i = 0; i < tuple_count; i++) {
        for (int j = 0; j < tuple_size; j++) {
            size_t len = strnlen(tuple_data[i][j], 4096);
            flattened[i * tuple_size + j] = (char*)malloc((len + 1) * sizeof(char));
            if (flattened[i * tuple_size + j] == NULL) {
                for (int k = 0; k < i * tuple_size + j; k++) {
                    free(flattened[k]);
                }
                free(flattened);
                return 1;
            }
            snprintf(flattened[i * tuple_size + j], len + 1, "%s", tuple_data[i][j]);
        }
    }

    char** result = adjacent_concatenation(flattened, tuple_count, tuple_size);
    if (result == NULL) {
        for (int i = 0; i < tuple_count * tuple_size; i++) {
            free(flattened[i]);
        }
        free(flattened);
        return 1;
    }

    int result_count = tuple_count * (tuple_size - 1);
    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
        free(result[i]);
    }

    free(result);

    for (int i = 0; i < tuple_count * tuple_size; i++) {
        free(flattened[i]);
    }
    free(flattened);

    return 0;
}