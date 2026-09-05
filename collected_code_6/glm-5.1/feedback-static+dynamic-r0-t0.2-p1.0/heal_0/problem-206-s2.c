#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** adjacent_concat(const char** tuples, size_t count, size_t* result_count) {
    if (count < 2) {
        *result_count = 0;
        return NULL;
    }

    *result_count = count - 1;
    char** result = malloc((count - 1) * sizeof(char*));
    if (!result) {
        *result_count = 0;
        return NULL;
    }

    for (size_t i = 0; i < count - 1; ++i) {
        size_t len1 = strlen(tuples[i]);
        size_t len2 = strlen(tuples[i + 1]);
        
        result[i] = malloc(len1 + len2 + 1);
        if (!result[i]) {
            for (size_t j = 0; j < i; ++j) {
                free(result[j]);
            }
            free(result);
            *result_count = 0;
            return NULL;
        }

        memcpy(result[i], tuples[i], len1);
        memcpy(result[i] + len1, tuples[i + 1], len2);
        result[i][len1 + len2] = '\0';
    }

    return result;
}

void free_concat_result(char** result, size_t count) {
    if (result) {
        for (size_t i = 0; i < count; ++i) {
            free(result[i]);
        }
        free(result);
    }
}

int main(void) {
    const char* tuples[] = {"Hello", "World", "C", "Programming"};
    size_t count = sizeof(tuples) / sizeof(tuples[0]);
    size_t result_count = 0;

    char** result = adjacent_concat(tuples, count, &result_count);

    if (result) {
        for (size_t i = 0; i < result_count; ++i) {
            printf("%s\n", result[i]);
        }
        free_concat_result(result, result_count);
    }

    return 0;
}