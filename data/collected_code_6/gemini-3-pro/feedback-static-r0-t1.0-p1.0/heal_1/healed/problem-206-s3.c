#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** concatenate_adjacent(char** tuple, int size, int* result_size) {
    if (tuple == NULL || size <= 0 || result_size == NULL) {
        return NULL;
    }

    *result_size = size - 1;
    if (*result_size == 0) {
        *result_size = 0;
        return NULL;
    }

    char** result = (char**)malloc(*result_size * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < *result_size; i++) {
        if (tuple[i] == NULL || tuple[i + 1] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t len1 = strlen(tuple[i]);
        size_t len2 = strlen(tuple[i + 1]);
        
        result[i] = (char*)malloc((len1 + len2 + 1) * sizeof(char));
        if (result[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        snprintf(result[i], len1 + len2 + 1, "%s%s", tuple[i], tuple[i + 1]);
    }

    return result;
}

int main(void) {
    int size = 4;
    char* tuple[] = {"Hello", "World", "C", "Programming"};
    int result_size = 0;

    char** result = concatenate_adjacent(tuple, size, &result_size);

    if (result != NULL) {
        for (int i = 0; i < result_size; i++) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    }

    return 0;
}