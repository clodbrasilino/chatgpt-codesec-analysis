#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

char** concatenate_adjacent(const char** tuples, size_t size, size_t* out_size) {
    if (!tuples || !out_size || size == 0) {
        if (out_size) *out_size = 0;
        return NULL;
    }

    *out_size = size - 1;
    char** result = (char**)malloc(*out_size * sizeof(char*));
    if (!result) {
        *out_size = 0;
        return NULL;
    }

    for (size_t i = 0; i < *out_size; ++i) {
        if (!tuples[i] || !tuples[i+1]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            *out_size = 0;
            return NULL;
        }
        
        size_t len1 = strnlen(tuples[i], MAX_STR_LEN);
        size_t len2 = strnlen(tuples[i+1], MAX_STR_LEN);
        
        result[i] = (char*)malloc(len1 + len2 + 1);
        if (!result[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            *out_size = 0;
            return NULL;
        }
        
        snprintf(result[i], len1 + len2 + 1, "%s%s", tuples[i], tuples[i+1]);
    }

    return result;
}

int main(void) {
    const char* input_tuples[] = {"Hello", "World", "This", "Is", "C"};
    size_t input_size = sizeof(input_tuples) / sizeof(input_tuples[0]);
    size_t result_size = 0;

    char** result = concatenate_adjacent(input_tuples, input_size, &result_size);

    if (result) {
        for (size_t i = 0; i < result_size; ++i) {
            printf("%s\n", result[i]);
            free(result[i]);
        }
        free(result);
    } else {
        printf("Failed to concatenate.\n");
    }

    return 0;
}