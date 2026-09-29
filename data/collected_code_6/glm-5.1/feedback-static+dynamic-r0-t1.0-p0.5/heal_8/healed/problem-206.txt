#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char** adjacent_concat(const char** tuples, int count) {
    if (tuples == NULL || count < 2) {
        return NULL;
    }

    int result_count = count - 1;
    char** result = (char**)malloc(result_count * sizeof(char*));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < result_count; i++) {
        if (tuples[i] == NULL || tuples[i + 1] == NULL) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
            return NULL;
        }

        size_t len1 = strnlen(tuples[i], SIZE_MAX);
        size_t len2 = strnlen(tuples[i + 1], SIZE_MAX);

        if (len1 > SIZE_MAX - len2 || len1 + len2 > SIZE_MAX - 1) {
            for (int j = 0; j < i; j++) {
                free(result[j]);
            }
            free(result);
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

        memcpy(result[i], tuples[i], len1);
        memcpy(result[i] + len1, tuples[i + 1], len2);
        result[i][total_len] = '\0';
    }

    return result;
}

void free_concat_result(char** result, int count) {
    if (result == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(result[i]);
    }
    free(result);
}

int main(void) {
    const char* tuples[] = {"Hello", "World", "C", "Programming"};
    int count = (int)(sizeof(tuples) / sizeof(tuples[0]));

    char** result = adjacent_concat(tuples, count);
    if (result == NULL) {
        return EXIT_FAILURE;
    }

    int result_count = count - 1;
    for (int i = 0; i < result_count; i++) {
        printf("%s\n", result[i]);
    }

    free_concat_result(result, result_count);

    return EXIT_SUCCESS;
}